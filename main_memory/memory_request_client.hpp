class memory_request_client_t {
    public:
        package_state_t status;
        uint32_t readyAt;
        bool waiting_DRAM;

        memory_request_client_t();
        virtual ~memory_request_client_t();

        virtual void updatePackageUntreated(uint32_t stallTime);
        virtual void updatePackageReady(uint32_t stallTime);
        virtual void updatePackageWait(uint32_t stallTime);
        virtual void updatePackageFree(uint32_t stallTime);
};