* Port everything from old awrts
    * Unit types  [done]
    * Map loader  [done]
    * RTS camera  [done]
    * Unit movement [not started]
    * Unit selection & orders [not started]
    * Debug keys  [not started]
    * Physics     [not started]

* Fix avoidance (implement from scratch)
* Port navigation from old awrts
* Raycast batching: all raycasting is performed before game logic, instead of when requested, results are retrieved by entity handle
* Unit movement batching (units are not moved immediately; instead, it is queued, and 'movement operator' performs collision checking and moves units if no collisions detected)

* Write obj importer to replace Irrlicht's one [done]
* Replace irrlicht device with SFML
* Write OpenGL renderer (it's easy actually)
* Write spatial hierarchy (octree? kd? bvh?)

* Write custom GUI
    * Port console GUI from old awrts [not started]
