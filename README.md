# Serine

A lightweight (STL-only), header-only C++11, free and open source bidirectional serialization system.

Loosely based on [Cereal](https://uscilab.github.io/cereal/)'s code syntax.

## Features

* Supports 2 serialization paradigms:
    * named data entries (e.g. for XML, JSON, BSON, MsgPack...)
    * unnamed, linearly wrote/read data (tight packing)
* Different (de)serialization backends through inheritance and virtual methods.
* No templating of the serialization methods.
* Fully harnessing C++11's power to only do a single data copy/read/write per operation, nullifying
  potential run-time object copying overhead.
* Flexible lightweight data container wrappers (forward iterators) to allow for (de)serialization
  of arrays, vectors, linked lists and more, regardless of their actual implementation.
  (A default STL-compatible container wrapper is available through `serine::contain_stl()`)

## Extending

As to avoid templating, adding new non-struct/class type handling to an `Archiver` is not directly
possible. This can however be worked around by creating your own `serine::Archiver`-inheriting
base or real class, extend it to allow your new types [in/out]takes, as well as making your own
`serine::Serializable`-like interface, madating a `serialize()` method taking your new serializer
as parameter.

## Limitations

* As Serine's syntax is both bidirectional and named, (de)serialization must both be statically
  ordered and entry-named. This as well refrains you to bulk serialize data in the same fashion
  Cereal allows for.
* Serine is only supposed to be a serialization structure, not a fully fledged data loading/saving
  framework. As such, only basic memory/file-based serializers are available (as a default and
  reference implementation). Applications are supposed to supply their own format handlers.

## Notes

No 16-bit character/string serialization is provided (by default). This is intended, as using
16-bit chars most likely implies the usage of UTF-16, which takes the worst parts of both UTF-8
and UTF-32 and turns it into a horrid hybrid encoding.
Refer to [utf8everywhere.org](http://utf8everywhere.org/) for more information.
