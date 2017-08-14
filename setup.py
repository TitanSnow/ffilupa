from setuptools import setup

setup(
    name='ffilupa',
    packages=['ffilupa'],
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["ffibuilder_lua.py:ffibuilder"],
    install_requires=["cffi>=1.0.0", "six>=1.9.0"],
    test_suite='ffilupa.tests.suite',
)
