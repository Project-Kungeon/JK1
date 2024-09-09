using System.IO;
using UnrealBuildTool;

public class ThirdParty : ModuleRules
{
    public ThirdParty(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        if(Target.Platform == UnrealTargetPlatform.Win64)
        {

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_atomic-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_chrono-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_container-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_context-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_contract-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_coroutine-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_date_time-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_exception-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_fiber-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_filesystem-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_graph-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_iostreams-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_json-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_locale-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_log_setup-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_log-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_math_c99f-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_math_c99l-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_math_c99-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_math_tr1f-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_math_tr1l-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_math_tr1-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_nowide-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_prg_exec_monitor-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_program_options-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_random-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_regex-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_serialization-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_stacktrace_noop-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_stacktrace_windbg_cached-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_stacktrace_windbg-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_system-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_test_exec_monitor-vc143-mt-x64-1_83.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_thread-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_timer-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_type_erasure-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_unit_test_framework-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_url-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_wave-vc143-mt-x64-1_83.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Lib", "libboost_wserialization-vc143-mt-x64-1_83.lib"));

            PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Include", "boost_1_83_0"));
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "BoostAsio", "Include", "boost_1_83_0"));

            PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "ProtobufCore", "Include"));
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ProtobufCore", "Include"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ProtobufCore", "Lib", "libprotobufd.lib"));

            PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
        }
        
    }
}