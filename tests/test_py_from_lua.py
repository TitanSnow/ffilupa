import pytest
from ffilupa import *


lua = LuaRuntime()


def test_LuaObject_operators():
    a = lua._G.python.to_luaobject(22)
    b = lua._G.python.to_luaobject(3)
    c = 22
    d = 3
    assert a.typename() == 'number'
    assert b.typename() == 'number'
    assert int(a) is c
    assert int(b) is d
    for op in '+ - * / // % ** & | ^ << >> == < <= > >= !='.split():
        exec('assert (a{0}b) == (c{0}d)'.format(op))
        exec('assert (a{0}d) == (c{0}d)'.format(op))
        exec('assert (c{0}b) == (c{0}d)'.format(op))
    for op in '- ~'.split():
        exec('assert {0}a == {0}c'.format(op))


def test_not_impl():
    with pytest.raises(TypeError, message='unsupported operand type(s) for +: \'LuaObject\' and \'LuaObject\''):
        lua.table() + lua.table()
    class R:
        def __radd__(self, other):
            return 'Awd!'
    tb = lua.table()
    r = R()
    assert tb + r == 'Awd!'

    lua_ne = LuaRuntime(encoding=None)
    with pytest.raises(TypeError, message=b'unsupported operand type(s) for +: \'LuaObject\' and \'LuaObject\''):
        lua_ne.table() + lua_ne.table()


def test_bytes():
    assert bytes(lua.table()).startswith(b'table: ')


def test_str():
    assert str(lua.table()).startswith('table: ')
    lua_ne = LuaRuntime(encoding=None)
    assert bytes(lua.table()).startswith(b'table: ')
    with pytest.raises(ValueError):
        str(lua_ne.table())


def test_table_operators():
    tb = lua.table()

    assert tb.第六夜想曲 == None
    assert tb['第六夜想曲'] == None
    tb.第六夜想曲 = '幽色咏叹调'
    assert tb.第六夜想曲 == '幽色咏叹调'
    assert tb['第六夜想曲'] == '幽色咏叹调'
    del tb.第六夜想曲
    assert tb.第六夜想曲 == None
    assert tb['第六夜想曲'] == None

    assert tb.第六夜想曲 == None
    assert tb['第六夜想曲'] == None
    tb['第六夜想曲'] = '幽色咏叹调'
    assert tb.第六夜想曲 == '幽色咏叹调'
    assert tb['第六夜想曲'] == '幽色咏叹调'
    del tb['第六夜想曲']
    assert tb.第六夜想曲 == None
    assert tb['第六夜想曲'] == None

    tb.__dict__['edit_mode'] = True
    tb.卡莲 = '卡斯兰娜'
    tb.__dict__['edit_mode'] = False
    assert tb.卡莲 == '卡斯兰娜'
    assert tb['卡莲'] == None
    del tb.卡莲
    assert tb.卡莲 == None
    assert tb['卡莲'] == None

    tb.__dict__['edit_mode'] = True
    tb.卡莲 = '卡斯兰娜'
    assert tb.卡莲 == '卡斯兰娜'
    assert tb['卡莲'] == None
    del tb.卡莲
    with pytest.raises(AttributeError): tb.卡莲
    assert tb['卡莲'] == None
    tb.__dict__['edit_mode'] = False