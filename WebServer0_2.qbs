import qbs

CppApplication {
    consoleApplication: true
    files: [
        "c_global.cpp",
        "c_global.h",
        "c_option.cpp",
        "c_option.h",
        "c_reactorwithstruct.cpp",
        "c_reactorwithstruct.h",
        "csingleton.h",
        "main.cpp",
        "reactor.cpp",
        "reactor.h",
        "tcp.cpp",
        "tcp.h",
        "webserverhandlerprocess.cpp",
        "webserverhandlerprocess.h",
        "webserverobject.cpp",
        "webserverobject.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
