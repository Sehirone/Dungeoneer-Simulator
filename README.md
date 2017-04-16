Dungeoneer simulator - symulator bohatera budz¹cego siê w dziwnej przestrzeni zbudowanej jedynie z pustych pól i niemo¿liwych do przejœcia #.
    Nasz bohater uporczywie szuka wyjœcia, jednak na swojej drodze trafia jedynie na hordy przeciwników a ka¿de wyjœcie prowadzi jedynie do kolejnego poziomu z którego nie ma powrotu.
    Program sk³ada siê z klas:
    level - odpowiedzialna za, proceduralne generowanie poziomów, informowanie o obecnoœci w poz x,y œciany lub drogi, wyrysowywanie samej siebie oraz postaci znajdujaych sie na mapie(dodawane w postaci literki poprzez funkcje, po œmierci usuwane)
    character - klasa bazowa dla klas enemy/player, zawiera wspólne dane i funkcje takie jak pozycje, cechy niezbêdne do walki, informujace o stanie postaci oraz odpowiedzialne za zmiane pozycji
    enemy - dziediczy po character + zawiera informacje charakterystyczne dla wroga
    player - dziedziczy po character + zawiera informacje charakterystyczne dla gracza

    Z grubsza taki jest zamys³, g³ównym celem projektu jest przyswojenie oraz zaimplementowanie algorytmu generowanie proceduralnego labiryntu perfekcyjnego nastepnie wrzucenie do niego bohatera którego celem jest znalezienie wyjœcia.
    Wp³yw u¿ytkownika na symulacje to nadanie imienia oraz podanie wstêpnych porz¹danych statystyk.

    Plan podstawowy: j.w.
    Dodatki zbedne, aczkolwiek mo¿liwe (w kolejnosci prawdopodobienstwa wprowadzenia): pu³apki, g³ód/jedzenie, przedmioty na ziemi, mozliwosc wyboru klasy bohatera, druzyna bohaterow