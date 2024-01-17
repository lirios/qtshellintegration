liri_add_module(QtShellIntegration
    DESCRIPTION
        "Integration between Wayland shells and Qt applications"
    SOURCES
        sessionlocksurface.cpp sessionlocksurface.h
        layersurface.cpp layersurface.h layersurface_p.h
    PUBLIC_LIBRARIES
        Qt6::Core
        Qt6::Gui
        Qt6::QmlIntegration
        Qt6::WaylandClient
    LIBRARIES
        Qt6::GuiPrivate
    PKGCONFIG_DEPENDENCIES
        Qt6Core
        Qt6QmlIntegration
        Qt6Gui
        Qt6WaylandClient
)

ecm_qt_declare_logging_category(
    QtShellIntegration
    HEADER "qtshellintegrationlogging.h"
    IDENTIFIER "lcQtShellIntegration"
    CATEGORY_NAME "liri.qtshellintegration"
    DEFAULT_SEVERITY "Info"
)

liri_finalize_module(QtShellIntegration)
