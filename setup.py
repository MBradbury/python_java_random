from distutils.core import setup, Extension
setup(name="java_random", version="1.0.1",
      description="Provides a fast implementation of the Java random number generator",
      author="Matthew Bradbury",
      license="MIT",
      url="https://github.com/MBradbury/python_java_random",
      ext_modules=[Extension("java_random", ["src/java_random_module.c", "src/java_random.c"])],
      classifiers=["Programming Language :: Python :: 2",
                   "Programming Language :: Python :: 3",
                   "Programming Language :: Python :: Implementation :: CPython"]
)
