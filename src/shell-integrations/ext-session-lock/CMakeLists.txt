find_package(XkbCommon REQUIRED)

qt6_add_plugin(liri-ext-session-lock
    SHARED
    qwaylandlockscreenintegration.cpp qwaylandlockscreenintegration_p.h
    qwaylandlockscreenintegrationplugin.cpp
    qwaylandextsessionlock.cpp qwaylandextsessionlock_p.h
)

qt6_generate_wayland_protocol_client_sources(liri-ext-session-lock
    FILES
        ${WaylandProtocols_DATADIR}/staging/ext-session-lock/ext-session-lock-v1.xml
)

target_link_libraries(liri-ext-session-lock
    PRIVATE
        Liri::QtShellIntegration
        Qt6::WaylandClient
        Qt6::WaylandClientPrivate
        XkbCommon::XkbCommon
)

install(TARGETS liri-ext-session-lock
        DESTINATION ${KDE_INSTALL_PLUGINDIR}/wayland-shell-integration)
