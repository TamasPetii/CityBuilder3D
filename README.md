# City Builder Game

## Játék Ismertető

A City Builder játékunk egy 3D-s városépítő szimulátor, ahol a játékos a város polgármestere, így a teljes város fejlődése a felhasználó kezében van. Fontos, hogy egy jól felépített, kiegyensúlyozott város megteremtése a cél, ennek érdekében lakóhelyeket, munkahelyeket és további épületeket kell építeni, amik biztosítáják egyrészt hónapról hónapra a város pénzügyeit, másrészt a polgárok elégedettségét. A játékos, ha a várost pénzügyi csődbe viszi, vagy nem megfelelően építi fel a város struktúráját, így boldogtalanok a polgárok, illetve ha végzetes esemény következik be (meteor zápor), akkor a játék véget érhet. 

A játékot OpenGL-ben alkottuk meg C++ nyelv alatt. A 3D világhoz szükséges rétegeket mi építettük fel, azaz magát a játék engine-t, a objektumok renerelését, shadereket, alakzatokat, illetve a fényt mi hoztuk létre. A játéktér 5 alap alakzatból áll: Kocka, Gömb, Henger, Gúla, Kúp és ezeknek a kombinációjából állnak komplex alakzatok, amiket a játékban ténylegesn láthattok. (Pl: Fa 4 db kúpból áll, amik kicsit el vannak tolva, hogy fa hatást keltsünk.)
Továbáá a játék játszható 2D, 2.5D, 3D-ben egyaránt, ezt a grafikai beállításoknál lehet testre szabni.

A játék engine megvalósításához felhasznált ötletek nagyban köszöhetőek a Számítógépes Grafika (IP - 18KVISZGG) tárgyon tanultaknak, illetve a https://learnopengl.com/ weboldalon fellelhető forrásoknak. Azonban a project főleg csak az ötletek gondolatmeneteit tartalmazza, a tényleges kódókat mi írtuk meg teljesen átalakítva, saját ötletekkel.

## Elkészített feladatok
- Alapfeladat (1.5)
- Tűzoltóság (1)
- Oktatás (1)
- Nyugdíj (0.5)
- Erdők (0.5)
- Járművek (1)
- Perzisztencia (0.5)
- Konfliktusos bontás (0.5)
- Metropolis (0.5)
- Katasztrófa (0.5)
- Haladóbb grafika (1)

## Navigálás a játékban

**WASD** : Kamera mozgatása <br>
**Bal klikk** : Kamera forgatása <br>
**Jobb klikk** : Építés, rombolás <br>
**R** : Épület forgatása <br>

## Játék Bemutató

Youtube videó: https://www.youtube.com/watch?v=ve_PdvcHhAM

#### Lobby
![Lobby](Images/Lobby.jpg)

#### Új játék
![NewGame](Images/NewGame.jpg)

#### Betöltött játékállás
![InGame](Images/InGame.jpg)

#### Autók + Tűzoltás
![FireTruck](Images/FireTruck.jpg)

#### Meteor Zápor
![Meteors](Images/Meteors.jpg)

## CI/CD

**Test Code Coverage** <br>
https://szofttech-ab-2023.szofttech.gitlab-pages.hu/group-10/sajtoskifli/city_builder/coverage_report.html

**Static Code Analysis** <br>
https://szofttech-ab-2023.szofttech.gitlab-pages.hu/group-10/sajtoskifli/city_builder/cppcheck_analysis/index.html

**Generated Documentation** <br>
https://szofttech-ab-2023.szofttech.gitlab-pages.hu/group-10/sajtoskifli/city_builder/doxygen_documentation/index.html

## Felhasznált külső szoftverek

**ImGui:** https://github.com/ocornut/imgui/tree/docking <br>
**ImGui-FileDialog:** https://github.com/aiekick/ImGuiFileDialog <br>
**Stb-image:** https://github.com/nothings/stb/ <br>
**GLM:** https://github.com/g-truc/glm/ <br>
**GLFW:** https://github.com/glfw/glfw <br>
**GLEW:** https://github.com/nigels-com/glew <br>
**ASSIMP:** https://github.com/assimp/assimp <br>
