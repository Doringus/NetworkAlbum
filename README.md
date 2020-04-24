# NetworkAlbum OmSTU training task
Network album - simple client/server desktop application for sharing photos. Application based on flux architecture

Flux
====
![alt text](https://i.imgur.com/oHZ6yCi.png)


Application has:
- RootStore as top domain store. It manages global popups like album creation popup
- AlbumsStore as store for albums page. Manages list items
- AlbumStore as store for album page. Manages files and images, also stores conversation
- SessionsStore as generic store which contains sessions data. It does some stuff with sessions

Completed features
==================
- Sending images from server to client via tcp
- Scaling images before sending (if option is on) in different thread
- Server manages many sessions at the same time
- Separate chat for every session
- Multithreaded server
- All image manipulations on client: renaming, moving in folders
- Sending changes on server

In progress
==========
- Saving images after synchronizing in different folder (if option is on)
- Settings page
- Help page
- Easter egg
- Some ui/ux features

Bugs
====
- Random crashes when it is creating session (because of incorrect usage of iterators). Will be fixed in next commit

Screenshots
===========
Startup page

![](https://i.imgur.com/c3zBupB.png)
============================================

Create session popup

![](https://i.imgur.com/K0RVSwJ.png)
============================================

Albums page with message notification

![](https://i.imgur.com/UMeYZ9X.png)
============================================

Album page

![](https://i.imgur.com/1iRSkN3.png)
============================================

Client album page with move image popup

![](https://i.imgur.com/NeFwTND.png)
============================================

Server album page after synchronizing with client

![](https://i.imgur.com/hHxUI5Q.png)