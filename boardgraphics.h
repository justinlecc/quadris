
struct BoardGraphicsImpl;
class BoardGraphics {
  BoardGraphicsImpl * pImpl;
  
  BoardGraphics();
  static BoardGraphics * instance;
  static void cleanup();
public:
  static BoardGraphics * getInstance();
  ~BoardGraphics();
  
  void TurnOnGraphics();
  void TurnOffGraphics();
  
  void changeLevel();
  void changeScore();
  void changeHiScore();
  
  void changeNextBlock(char block_type);
  void drawCell(int row, int col, char block_type);
  void undrawCell(int row, int col);
  void gameOver();
  void restart();
  
};