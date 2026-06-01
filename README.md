📚 COZY BOOKISH TETRIS
Acesta este un joc de Tetris relaxant, cu o estetică inspirată din lumea cărților. În loc de blocuri colorate clasice, piesele reprezintă stive de cărți în ediții de colecție pe care trebuie să le organizezi frumos pe un raft de nuanța pergamentului. Scopul tău este să completezi rânduri pentru a aduna cât mai multe pagini citite.

🛠️ CUM SE DESCARCĂ ȘI CUM SE INSTALEAZĂ
Pentru a putea juca, ai nevoie de codul acestui joc și de librăria grafică Raylib instalată pe calculatorul tău.

Pasul 1: Descarcă librăria Raylib pentru Windows. Cel mai simplu mod este să descarci pachetul complet gata configurat (w64devkit) de pe site-ul oficial Raylib sau de pe contul lor de GitHub. Varianta recomandată este Raylib versiunea 5.5 cu MinGW inclus.

Pasul 2: Instalează Raylib pe calculatorul tău, de preferat direct pe o partiție accesibilă, de exemplu în folderul:

D:/raylib-5.5_win64_mingw-w64 sau C:/raylib

Pasul 3: Pune toate fișierele codului (jiustrate mai jos) în același folder, oriunde dorești pe calculatorul tău:

main.c, screen.c, screen.h, input.c, input.h, measure.h și fișierul makefile

Pasul 4: Deschide o fereastră de terminal (Command Prompt sau PowerShell) exact în folderul unde ai pus fișierele jocului.

Pasul 5: Scrie în terminal următoarea comandă și apasă Enter:

Bash
mingw32-make
Această comandă va compila automat tot codul, se va lega de librăria Raylib descărcată și va crea un fișier executabil în folderul tău. După ce s-a terminat compilarea, poți porni jocul dând dublu-click pe executabilul nou apărut.

☕ CUM SE JOACĂ ȘI CARE SUNT CONTROALELE
Când pornești jocul, vei intra în meniul principal. Dai click pe butonul OPEN BOOK ca să începi lectura. Cărțile vor începe să cadă singure de sus.

⬅️ Săgeată Stânga : Mută cărțile spre stânga. Dacă o ții apăsată, piesa va continua să meargă fluid în acea direcție.

➡️ Săgeată Dreapta : Mută cărțile spre dreapta, funcționând la fel de fluid la apăsarea lungă.

⬆️ Săgeată Sus / [Space] : Rotește stiva de cărți la 90 de grade pentru a o putea potrivi în spațiile înguste de pe raft.

⬇️ Săgeată Jos : Activează scanarea rapidă a paginii. Cât timp o ții apăsată, cartea va cădea mult mai repede spre podea ca să nu mai aștepți după ea.

📋 Regulile bibliotecii
Pe măsură ce completezi linii orizontale fără spații libere, acele cărți vor fi subliniate cu o animație galbenă de textmarker și vor dispărea, adăugându-ți puncte la contorul PAGES READ din dreapta.

Jocul devine din ce în ce mai rapid pe măsură ce citești mai multe pagini. Ai grijă să nu lași cărțile să se adune până în tavan, altfel sesiunea de lectură se va termina!

✨ Spor la citit! ✨
