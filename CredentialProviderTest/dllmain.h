// dllmain.h: 模块类的声明。

namespace glasssix
{
    namespace hello
    {
        class CCredentialProviderTestModule : public ATL::CAtlDllModuleT<CCredentialProviderTestModule>
        {
        public:
            DECLARE_LIBID(LIBID_CredentialProviderTestLib)
            DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CREDENTIALPROVIDERTEST, "{e03d8900-55b1-40b4-ab5b-909c429ed5f7}")
        };
    }
}

extern class glasssix::hello::CCredentialProviderTestModule atl_module_;
