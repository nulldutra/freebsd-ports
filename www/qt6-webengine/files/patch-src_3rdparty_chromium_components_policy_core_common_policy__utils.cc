--- src/3rdparty/chromium/components/policy/core/common/policy_utils.cc.orig	2024-01-30 07:53:34 UTC
+++ src/3rdparty/chromium/components/policy/core/common/policy_utils.cc
@@ -28,7 +28,7 @@ bool IsPolicyTestingEnabled(PrefService* pref_service,
     return true;
   }
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (channel == version_info::Channel::DEV) {
     return true;
   }
