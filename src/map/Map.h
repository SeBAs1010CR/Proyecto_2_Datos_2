
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
    void ConstruirAdyacencia();
    int encontrarNodoInicial();
    int contarCeldasLibres();
    void GenerarObstaculo();
};