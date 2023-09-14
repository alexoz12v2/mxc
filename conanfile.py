from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMakeDeps
from conan.tools.cmake import CMakeToolchain
from conan.tools.scm import Git


class MXCMathRecipe(ConanFile):
    name = "mxc"
    version = "0.0.1"  # coincides with cmake's project declared version

    author = "alexoz12v2 oboken1974@hotmail.it"
    license = "BSD 2-Clause License"
    url = "https://github.com/alexoz12v2/mxc"
    description = "Minimal math library, part of the MXC collection of utilities"
    topics = ("math", "numeric")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "link_time_optimized": [True, False]}
    default_options = {"shared": False, "fPIC": True, "link_time_optimized": False}

    # Sources (use source method if source is not present locally)
    export_sources = "CMakeLists.txt", "src/*"

    #    def sources(self):
    #        git = Git(self)
    #        git.clone

    def validate(self):
        check_min_cppstd(self, "20")

    # dependencies
    def requirements(self):
        self.requires("catch2/3.4.0")
        self.requires("fmt/10.1.1")

    # information for each component (.lib) we want to provide. each component needs to define
    # 1) libs 2) requires 3) set_property
    def package_info(self):
        self.cpp_info.components["core"].libs = ["core"]
        self.cpp_info.components["core"].set_property = ["cmake_target_name", "mxc::core"]

        self.cpp_info.components["platform"].libs = ["platform"]
        self.cpp_info.components["platform"].requires = ["core"]
        self.cpp_info.components["platform"].set_property = ["cmake_target_name", "mxc::platform"]

        self.cpp_info.components["math"].libs = ["math"]
        self.cpp_info.components["math"].requires = ["platform"]
        self.cpp_info.components["math"].set_property = ["cmake_target_name", "mxc::math"]

    def config_options(self):
        # TODO: How can This be modified to support cross compilation
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    # this is equivalent to having attribute generator = "CMakeToolchain", but in the member you can do more
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info_libs = ["mxc"]
        # conan sets libdirs = ["lib"] and includedirs = ["include"] by default
