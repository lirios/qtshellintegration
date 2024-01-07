ecm_add_qml_module(QtShellIntegrationPlugin
    URI Liri.QtShellIntegration
    VERSION 1.0
    CLASS_NAME Plugin
    NO_GENERATE_PLUGIN_SOURCE
    DEPENDENCIES QtQuick
)

target_sources(QtShellIntegrationPlugin PRIVATE qtshellintegrationplugin.cpp)

target_link_libraries(QtShellIntegrationPlugin
    PRIVATE
        Qt6::Qml
        Liri::QtShellIntegration
)

ecm_finalize_qml_module(QtShellIntegrationPlugin)
