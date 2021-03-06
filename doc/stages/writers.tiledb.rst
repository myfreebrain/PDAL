.. _writers.tiledb:

readers.tiledb
==============

Implements `TileDB`_ 1.4.1+ reads from an array.

.. plugin::

.. streamable::

Example
-------

.. code-block:: json

  [
      {
          "type":"readers.las",
          "array_name":"input.las"
      },
      {
          "type":"writers.tiledb",
          "array_name":"output_array"
      }
  ]


Options
-------

array_name
  `TileDB`_ array to write to. [Required]

config_file
  `TileDB`_ configuration file [Optional]

tile_data_capacity
  Number of points per tile [Optional]

x_tile_size
  Tile size (x) in a Cartesian projection [Optional]

y_tile_size
  Tile size (y) in a Cartesian projection [Optional]

z_tile_size
  Tile size (z) in a Cartesian projection [Optional]

chunk_size
  Point cache size for chunked writes [Optional]

compression
  TileDB compression type for attributes, default is None [Optional]

compression_level
  TileDB compression level for chosen compression [Optional]

stats
  Dump query stats to stdout [Optional]


.. _TileDB: https://tiledb.io
