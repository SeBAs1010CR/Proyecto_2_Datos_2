
class Map{

private:
    int filas;
    int columnas;
    int** grid;
    int** MatrizAdyacencia;
    float probObstaculo;
    int totalNodos;

public:

    Map(int x, int y);
    ~Map();
    // MAPA
    void ConstruirAdyacencia();
    int encontrarNodoInicial();
     // BFS / DIJKSTRA
    int contarCeldasLibres();
    void GenerarObstaculo();
    // GETTERS
    int** getAdjacencyMatrix();

    int getTotalNodes();

    int** getGrid();
    //Linea vista
        bool lineOfSight(
        int x1,
        int y1,
        int x2,
        int y2
    );
};