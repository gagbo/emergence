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

- User can run emergence from the command line

  * User can set a count of Agents to populate the World

- User can interact with the simulation through menus

  * User can do what they want at the moment they want

    + Triggering a menu pauses the simulation

    + Finishing the menu continues the simulation

  * User can pause/continue/restart simulation through menu

  * User can add Entity through menu

- User can interact with the simultion through the viewing panel

  * User can do what they want at the moment they want

    + Triggering a menu pauses the simulation

    + Finishing the menu continues the simulation

  * User can do everything that's possible through menu via clicking on the map

    + All actions that need a position have default fields to the position of the click

    + All actions that need an Entity have default fields to one of the entity under cursor

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
