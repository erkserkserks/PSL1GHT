EXPORT(sysProcessExit, 0xe6f2c1e7);
EXPORT(sysProcessExitSpawn2, 0x67f9fedb);

EXPORT(sysSpuElfGetInformation, 0x1ed454ce);
EXPORT(sysSpuElfGetSegments, 0xdb6b3250);
EXPORT(sysSpuRawLoad, 0x893305fa);
EXPORT(sysSpuRawImageLoad, 0xb995662e);
EXPORT(sysSpuImageClose, 0xe0da8efd);
EXPORT(sysSpuImageImport, 0xebe5f72f);

EXPORT(sys_ppu_thread_exit, 0xaff080a4);
EXPORT(sys_ppu_thread_create_ex, 0x24a1ea07);
EXPORT(sys_ppu_thread_get_id, 0x350d454e);
EXPORT(sys_ppu_thread_register_atexit, 0x3dd4a957);
EXPORT(sys_interrupt_thread_disestablish, 0x4a071d98);
EXPORT(sys_ppu_thread_once, 0xa3e3be68);
EXPORT(sys_ppu_thread_unregister_atexit, 0xac6fc404);
EXPORT(sys_initialize_tls, 0x744680a2);
EXPORT(sys_time_get_system_time, 0x8461e528);
EXPORT(sys_prx_exitspawn_with_level, 0xa2c7ba64);

EXPORT(sysLwMutexCreate, 0x2f85c0ef);
EXPORT(sysLwMutexDestroy, 0xc3476d0c);
EXPORT(sysLwMutexLock, 0x1573dc3f);
EXPORT(sysLwMutexTryLock, 0xaeb78725);
EXPORT(sysLwMutexUnlock, 0x1bc200f4);

EXPORT(sysLwCondSignalAll, 0xe9a1bd84);
EXPORT(sysLwCondSignal, 0xef87a695);
EXPORT(sysLwCondDestroy, 0x1c9a942c);
EXPORT(sysLwCondWait, 0x2a6d9d51);
EXPORT(sysLwCondCreate, 0xda0eb71a);
