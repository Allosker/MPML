# MPML -- Multi-Purpose Math Library

// Brief

MPML is a small math library that implements basic mathematical types such as:

2,3,4 dimensional vectors,
(general vector type)
2,3,4 dimensional matrices,
(general matrix type)

*General types are those whose members can only be accessed through indexing, thus making them less user friendly, they are also quite expensive since algorithms such as the Row/Column-major index mapping formula must be used for them to work (e.g. 4D matrices (2x2x2x2)), and even though those types may not be used that often, the library tends to be multi-purpose for any general usage.

However some other types such as Ranges, and Quaternions alongside Angles are defined.



This little library is mainly for me, I want to create my very own ecosystem!
And I hope this library will be part of a much larger system!

This library is also focused on maths applicable to the graphics programming world, albeit a general library.
As such, all my libraries respectively based on: openGL, Vulkan, and DirectX will be built using this math library at their core.


