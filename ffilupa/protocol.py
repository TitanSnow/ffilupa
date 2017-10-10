"""module contains python-to-lua protocols"""


from __future__ import absolute_import, unicode_literals
__all__ = tuple(map(str, ('as_attrgetter', 'as_itemgetter', 'as_function', 'as_is', 'Py2LuaProtocol', 'IndexProtocol')))


class Py2LuaProtocol(object):
    def __init__(self, obj):
        super(Py2LuaProtocol,self).__init__()
        self.obj = obj

class IndexProtocol(Py2LuaProtocol):
    """
    Control the access way for python object in lua.

    * ``ITEM``: indexing will be treat as item getting/setting.
    * ``ATTR``: indexing will be treat as attr getting/setting.

    Example:

    ..
        ## doctest helper
        >>> from ffilupa import *
        >>> runtime = LuaRuntime()

    ::

        >>> awd = {'get': 'awd'}
        >>> runtime._G.awd = awd
        >>> runtime.eval('awd.get')
        'awd'
        >>> runtime._G.awd = Py2LuaProtocol(awd, Py2LuaProtocol.ATTR)
        >>> runtime.eval('awd:get("get")')
        'awd'

    Default behavior is for objects have method ``__getitem__``,
    indexing will be treat as item getting/setting; otherwise
    indexing will be treat as attr getting/setting.
    """
    ITEM = 1
    ATTR = 2
    def __init__(self, obj, index_protocol=None):
        """
        Init self with ``obj`` and ``index_protocol``.

        ``obj`` is a python object.

        ``index_protocol`` can be ITEM or ATTR.
        If it's set to None, default behavior said above will
        take effect.
        """
        super(IndexProtocol, self).__init__(obj)
        if index_protocol is None:
            if hasattr(obj.__class__, '__getitem__'):
                index_protocol = self.__class__.ITEM
            else:
                index_protocol = self.__class__.ATTR
        self.index_protocol = index_protocol


class CFunctionProtocol(Py2LuaProtocol):
    pass


as_attrgetter = lambda obj: IndexProtocol(obj, IndexProtocol.ATTR)
as_itemgetter = lambda obj: IndexProtocol(obj, IndexProtocol.ITEM)
as_is = Py2LuaProtocol
as_function = CFunctionProtocol
