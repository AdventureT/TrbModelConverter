# TrbModelConverter
Originaly extracts model data from .trb files into fbx. 
You can find trbs in /your game directory/Data. 
Typically you will find model data in RegionAssets.trb or AssetPack.trb.
But since I added so much functionallity, it aims to be extractor for all trbs. 
It also aims to support many games including the Nicktoons Series, Barnyard, de Blob and more.

**This Programm is in very early development and doesn't support many trb files.**

## Supported Games :video_game:
Game Icon | Name | Plattform | Details | Progress 
------------ | -- | -- | -- |-------------
<img src="https://m.media-amazon.com/images/M/MV5BMDYzODY4MGItYTljMS00YmUxLWFkYjQtNmU1ODE1YmZmNGE3XkEyXkFqcGdeQXVyNjg1OTEwODQ@._V1_.jpg"  width="100" height="100" /> | Nicktoons Unite! | PS2 |One of the oldest trb formats and there is a intern tool which extracts data from **trbs into xml**. **Model format** is pretty weird; Vertices are extractable but not implemented yet. **Textures** are not in DDS format! | <img src="https://cdn.aduis.com/pics/ART_NR/607328_1.jpg"  width="300" height="100" />
<img src="https://images-na.ssl-images-amazon.com/images/I/612PJQSJUZL._SX466_.jpg"  width="300" height="100" /> | Nicktoons Attack of the Toybots | PS2 | **Model format** is pretty weird; Vertices are extractable but not implemented yet. **Textures** compressed with BTEC (TODO: Decompress BTEC's)! | <img src="https://cdn.aduis.com/pics/ART_NR/607328_1.jpg"  width="300" height="100" />
<img src="https://www.retroplace.com/pics/ps2/packshots/79275--spongebob-and-friends-battle-for-volcano-island.png"  width="300" height="100" /> | Nicktoons Battle for Volcano Island | PS2 | **Model format** is pretty weird; Vertices are extractable but not implemented yet. **Textures** compressed with BTEC (TODO: Decompress BTEC's) and have the extension ttl! | <img src="https://cdn.aduis.com/pics/ART_NR/607328_1.jpg"  width="300" height="100" />
<img src="https://community.bisafans.de/index.php?attachment/66859-cover-large-jpg/"  width="300" height="100" /> | de Blob | PC |**Extraction of models work!** **Textures** are in DDS format and easy to extract. Locale Text can be viewed in the viewlist. | <img src="https://images.obi.de/product/DE/1500x1500/591565_1.jpg"  width="300" height="100" />

## How to build :arrows_clockwise:
TrbModelConverter is written in c++ and can be opened in visual studio 2019. 
To build this programm you have to install the fbx sdk 2019 and include it in Properties.

Fbx SDK 2019.5 (Choose Visual Studio 2017): https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2019-5
