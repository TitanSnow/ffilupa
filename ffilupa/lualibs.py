import importlib
import itertools
import json
from collections import namedtuple
from pathlib import Path
import semantic_version as sv


__all__ = ('LuaLib', 'LuaLibs', 'get_lualibs', 'PkgInfo')


PkgInfo = namedtuple(
    'PkgInfo',
    (
        'include_dirs',
        'library_dirs',
        'libraries',
        'extra_compile_args',
        'extra_link_args',
        'version',
    ),
)


class LuaLib:
    def __init__(self, name, info):
        self.name = name
        self.info = info

    @property
    def version(self):
        return self.info.version

    @property
    def lua_version(self):
        mod = self.import_mod()
        return sv.Version(mod.ffi.string(mod.lib.LUA_RELEASE).decode()[4:])

    @property
    def modname(self):
        return 'ffilupa._' + self.name

    def import_mod(self):
        return importlib.import_module(self.modname)


class LuaLibs(list):
    def filter_version(self, spec):
        return LuaLibs(filter(lambda lualib: spec.match(lualib.version), self))

    def select_version(self, spec):
        try:
            return max(self.filter_version(spec), key=lambda ll: ll.version)
        except ValueError as e:
            raise ValueError('Required lua lib not found') from e

    def select_name(self, name):
        try:
            return next(filter(lambda lualib: lualib.name == name, self))
        except StopIteration as e:
            raise ValueError('Required lua lib not found') from e


def read_resource(filename):
    try:
        with (Path(__file__).parent / filename).open() as f:
            return f.read()
    except FileNotFoundError:
        import pkg_resources
        return pkg_resources.resource_string(__package__, filename).decode()


def get_lualibs():
    dic = json.loads(read_resource('lua.json'))
    for v in dic.values():
        v['version'] = sv.Version(v['version'])
    for k in dic:
        dic[k] = PkgInfo(**dic[k])
    return LuaLibs(itertools.starmap(LuaLib, dic.items()))
