Dungeoneer simulator - symulator bohatera budz�cego si� w dziwnej przestrzeni zbudowanej jedynie z pustych p�l i niemo�liwych do przej�cia #.
    Nasz bohater uporczywie szuka wyj�cia, jednak na swojej drodze trafia jedynie na hordy przeciwnik�w a ka�de wyj�cie prowadzi jedynie do kolejnego poziomu z kt�rego nie ma powrotu.
    Program sk�ada si� z klas:
    level - odpowiedzialna za, proceduralne generowanie poziom�w, informowanie o obecno�ci w poz x,y �ciany lub drogi, wyrysowywanie samej siebie oraz postaci znajdujaych sie na mapie(dodawane w postaci literki poprzez funkcje, po �mierci usuwane)
    character - klasa bazowa dla klas enemy/player, zawiera wsp�lne dane i funkcje takie jak pozycje, cechy niezb�dne do walki, informujace o stanie postaci oraz odpowiedzialne za zmiane pozycji
    enemy - dziediczy po character + zawiera informacje charakterystyczne dla wroga
    player - dziedziczy po character + zawiera informacje charakterystyczne dla gracza

    Z grubsza taki jest zamys�, g��wnym celem projektu jest przyswojenie oraz zaimplementowanie algorytmu generowanie proceduralnego labiryntu perfekcyjnego nastepnie wrzucenie do niego bohatera kt�rego celem jest znalezienie wyj�cia.
    Wp�yw u�ytkownika na symulacje to nadanie imienia oraz podanie wst�pnych porz�danych statystyk.

    Plan podstawowy: j.w.
    Dodatki zbedne, aczkolwiek mo�liwe (w kolejnosci prawdopodobienstwa wprowadzenia): pu�apki, g��d/jedzenie, przedmioty na ziemi, mozliwosc wyboru klasy bohatera, druzyna bohaterow