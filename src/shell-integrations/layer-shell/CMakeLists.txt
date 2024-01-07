find_package(XkbCommon REQUIRED)

qt6_add_plugin(liri-layer-shell
    SHARED
    qwaylandlayershellintegration.cpp qwaylandlayershellintegration_p.h
    qwaylandlayershellintegrationplugin.cpp
    qwaylandlayersurface.cpp qwaylandlayersurface_p.h
)

qt6_generate_wayland_protocol_client_sources(liri-layer-shell
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/wlr-layer-shell-unstable-v1.xml
)

target_link_libraries(liri-layer-shell
    PRIVATE
        Liri::QtShellIntegration
        Qt6::WaylandClient
        Qt6::WaylandClientPrivate
        XkbCommon::XkbCommon
)

install(TARGETS liri-layer-shell
        DESTINATION ${KDE_INSTALL_PLUGINDIR}/wayland-shell-integration)
