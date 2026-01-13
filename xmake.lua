-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/CommonLibSSE-NG")

-- set project
set_project("EldenCounter")
set_version("1.3.1")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")

-- set policies
set_policy("package.requires_lock", true)

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- require packages
add_requires("simpleini")

-- targets
target("EldenCounter")
    set_kind("shared")
    -- add dependencies to target
    add_deps("commonlibsse-ng")	
    add_packages("simpleini")

    add_defines("UNICODE", "_UNICODE")

    -- add commonlibsse-ng plugin
    -- add_rules("commonlibsse-ng.plugin", {
    --     name = "EldenCounter",
    --     author = "dtry",
    --     description = "SKSE64 plugin template using CommonLibSSE-NG"
    -- })

    -- add src files
    add_files("src/**.cpp")
    add_includedirs("include")
    add_includedirs("src")
    add_includedirs("src/include")
    add_headerfiles("src/**.h")
    add_headerfiles("include/**.h")
    set_pcxxheader("include/PCH.h")