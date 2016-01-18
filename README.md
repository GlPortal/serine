# Serine
A free and open bidirectional serialization system.

Supports 2 serialization paradigms:

* named data entries (e.g. for XML, JSON, BSON, MsgPack...)
* unnamed, linearly wrote/read data (tight packing)

As such when using Serine, (de)serialization order must be static, and each data entry must be
named.

Different (de)serialization backends are supported through inheritance and virtual methods.

Note no 16-bit character serialization is provided. This is intended, as using 16-bit chars most
likely implies the usage of UTF-16, which takes the worst parts of both UTF-8 and UTF-32 and turns
it into a horrid hybrid encoding.
Refer to [utf8everywhere.org](http://utf8everywhere.org/) for more information.
