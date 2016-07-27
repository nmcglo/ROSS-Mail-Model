#Introduction

This is an example model for use with [ROSS](http://github.com/carothersc/ROSS), the parallel discrete event simulation system at Rensselaer Polytechnic Institute.

This model simulates a simple postal network of mailboxes and post offices. Mailboxes send letters which are delivered to specific assigned post offices. The post offices process letters, determining if each letter that they recieve can be delivered to a local mailbox or if it must be routed to another post office.

This example model shows simple usage of scheduling new events, altering and reading message states, mapping of multiple LPs in a PDES system, and other intricacies of ROSS model development.


# Installation

This model requires the installation of [ROSS](http://github.com/carothersc/ROSS). After cloning this repository, follow the installation instructions in the ROSS repository to install.
