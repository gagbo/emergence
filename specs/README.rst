========================
Emergence specifications
========================
------------------------------------
Roadmap and demands for the software
------------------------------------

Vocabulary
==========

World
-----
The World is a zone where Entities can live and interact. It can be finite
(using "wrap around" to make Entities see the other side) or infinite.

Entity
------
An Entity is an object living in a World.

Agent
-----
An Agent is an autonomous Entity living in the World. It can move by itself according
to decisions made thanks to vision of its surroundings.

User needs
==========

- A user can run emergence from the command line
  - A user can set a count of Agents to populate the World

World specifications
====================
Should definitely be part of a Model, probably derived from
QGraphicsScene.

Entity specifications
=====================
Should definitely be part of a Model, probably derived from
QGraphicsItem.
Should support position and how to render

Agent specifications
====================

Structural subclasses
---------------------
Should support Ant and Predator ; and Ant should support roles to define.

Behavioural subclasses
----------------------
Should support Decisions and Actions
