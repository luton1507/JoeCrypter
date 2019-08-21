#ifndef _LMJOIN_H
#define _LMJOIN_H

#if __POCC__ >= 500
#pragma once
#endif

/* NetSetup API definitions */

#ifdef __cplusplus
extern "C" {
#endif

#define NETSETUP_JOIN_DOMAIN  0x00000001
#define NETSETUP_ACCT_CREATE  0x00000002
#define NETSETUP_ACCT_DELETE  0x00000004
#define NETSETUP_WIN9X_UPGRADE  0x00000010
#define NETSETUP_DOMAIN_JOIN_IF_JOINED  0x00000020
#define NETSETUP_JOIN_UNSECURE  0x00000040
#define NETSETUP_MACHINE_PWD_PASSED  0x00000080
#define NETSETUP_DEFER_SPN_SET  0x00000100
#define NETSETUP_JOIN_DC_ACCOUNT  0x00000200
#define NETSETUP_JOIN_WITH_NEW_NAME  0x00000400
#define NETSETUP_JOIN_READONLY  0x00000800
#define NETSETUP_DNS_NAME_CHANGES_ONLY  0x00001000
#define NETSETUP_INSTALL_INVOCATION  0x00040000
#define NETSETUP_AMBIGUOUS_DC  0x00001000
#define NETSETUP_NO_NETLOGON_CACHE  0x00002000
#define NETSETUP_DONT_CONTROL_SERVICES  0x00004000
#define NETSETUP_SET_MACHINE_NAME  0x00008000
#define NETSETUP_FORCE_SPN_SET  0x00010000
#define NETSETUP_NO_ACCT_REUSE  0x00020000
#define NETSETUP_IGNORE_UNSUPPORTED_FLAGS  0x10000000
#define NETSETUP_VALID_UNJOIN_FLAGS  (NETSETUP_ACCT_DELETE|NETSETUP_IGNORE_UNSUPPORTED_FLAGS|NETSETUP_JOIN_DC_ACCOUNT)
#define NETSETUP_PROCESS_OFFLINE_FLAGS  (NETSETUP_JOIN_DOMAIN|NETSETUP_DOMAIN_JOIN_IF_JOINED|NETSETUP_JOIN_WITH_NEW_NAME|NETSETUP_DONT_CONTROL_SERVICES|NETSETUP_MACHINE_PWD_PASSED)  

#if(_WIN32_WINNT >= 0x0601)
#define NETSETUP_PROVISION_DOWNLEVEL_PRIV_SUPPORT  0x00000001
#define NETSETUP_PROVISION_REUSE_ACCOUNT  0x00000002
#define NETSETUP_PROVISION_USE_DEFAULT_PASSWORD  0x00000004
#define NETSETUP_PROVISION_SKIP_ACCOUNT_SEARCH  0x00000008
#define NETSETUP_PROVISION_ONLINE_CALLER  0x40000000
#define NETSETUP_PROVISION_CHECK_PWD_ONLY  0x80000000
#endif /* _WIN32_WINNT >= 0x0601 */

typedef enum _NETSETUP_NAME_TYPE {
    NetSetupUnknown = 0,
    NetSetupMachine,
    NetSetupWorkgroup,
    NetSetupDomain,
    NetSetupNonExistentDomain,
#if (_WIN32_WINNT >= 0x0500)
    NetSetupDnsMachine
#endif
} NETSETUP_NAME_TYPE, *PNETSETUP_NAME_TYPE;

typedef enum _NETSETUP_JOIN_STATUS {
    NetSetupUnknownStatus = 0,
    NetSetupUnjoined,
    NetSetupWorkgroupName,
    NetSetupDomainName
} NETSETUP_JOIN_STATUS, *PNETSETUP_JOIN_STATUS;

NET_API_STATUS NET_API_FUNCTION NetJoinDomain(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,DWORD);
#if (_WIN32_WINNT >= 0x0601)
NET_API_STATUS NET_API_FUNCTION NetProvisionComputerAccount(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,DWORD,PBYTE*,DWORD*,LPWSTR*);
NET_API_STATUS NET_API_FUNCTION NetRequestOfflineDomainJoin(BYTE*,DWORD,DWORD,LPCWSTR);
#endif /* _WIN32_WINNT >= 0x0601 */
NET_API_STATUS NET_API_FUNCTION NetUnjoinDomain(LPCWSTR,LPCWSTR,LPCWSTR,DWORD);
NET_API_STATUS NET_API_FUNCTION NetRenameMachineInDomain(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,DWORD);
NET_API_STATUS NET_API_FUNCTION NetValidateName(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,NETSETUP_NAME_TYPE);
NET_API_STATUS NET_API_FUNCTION NetGetJoinInformation(LPCWSTR,LPWSTR*,PNETSETUP_JOIN_STATUS);
NET_API_STATUS NET_API_FUNCTION NetGetJoinableOUs(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,DWORD*,LPWSTR**);

#if (_WIN32_WINNT >= 0x0501)

#define NET_IGNORE_UNSUPPORTED_FLAGS  0x01

typedef enum _NET_COMPUTER_NAME_TYPE {
    NetPrimaryComputerName,
    NetAlternateComputerNames,
    NetAllComputerNames,
    NetComputerNameTypeMax
} NET_COMPUTER_NAME_TYPE, *PNET_COMPUTER_NAME_TYPE;

NET_API_STATUS NET_API_FUNCTION NetAddAlternateComputerName(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,ULONG);
NET_API_STATUS NET_API_FUNCTION NetRemoveAlternateComputerName(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,ULONG);
NET_API_STATUS NET_API_FUNCTION NetSetPrimaryComputerName(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,ULONG);
NET_API_STATUS NET_API_FUNCTION NetEnumerateComputerNames(LPCWSTR,NET_COMPUTER_NAME_TYPE,ULONG,PDWORD,LPWSTR**);

#endif /* _WIN32_WINNT >= 0x0501 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)

#define NETSETUP_PROVISIONING_PARAMS_WIN8_VERSION  0x00000001
#define NETSETUP_PROVISIONING_PARAMS_CURRENT_VERSION  0x00000002

typedef struct _NETSETUP_PROVISIONING_PARAMS {
    DWORD dwVersion;
    LPCWSTR lpDomain;
    LPCWSTR lpHostName;
    LPCWSTR lpMachineAccountOU;
    LPCWSTR lpDcName;
    DWORD dwProvisionOptions;
    LPCWSTR *aCertTemplateNames;
    DWORD cCertTemplateNames;
    LPCWSTR *aMachinePolicyNames;
    DWORD cMachinePolicyNames;
    LPCWSTR *aMachinePolicyPaths;
    DWORD cMachinePolicyPaths;
    LPWSTR lpNetbiosName;
    LPWSTR lpSiteName;
    LPWSTR lpPrimaryDNSDomain;
} NETSETUP_PROVISIONING_PARAMS, *PNETSETUP_PROVISIONING_PARAMS;

NET_API_STATUS NET_API_FUNCTION NetCreateProvisioningPackage(PNETSETUP_PROVISIONING_PARAMS, PBYTE *, DWORD *, LPWSTR *);
NET_API_STATUS NET_API_FUNCTION NetRequestProvisioningPackageInstall(BYTE *, DWORD, DWORD, LPCWSTR, PVOID);

#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN8 */

#ifdef __cplusplus
}
#endif

#endif /* _LMJOIN_H */