import java.io.*;
import java.util.*;

public class App {
  /*
   * public static void main(String[] args) {
   * int tablero[][] = { { 1, 10 }, { 4, 10 } };
   * int reinas = 2;
   * int torres = 0;
   * int tablerolleno[][] = { { 0, 0, }, { 0, 0 } };
   * int pesosMax = 0;
   * int peso = 0;
   * 
   * System.out.println(estopa(tablero, reinas, torres, tablerolleno, pesosMax,
   * peso));
   * 
   * }
   */

  public static int estopa(int T[][], int r, int t, int tL[][], int pM, int p) {
    /*
     * for (int i = 0; i < tL.length; i++) {
     * for (int j = 0; j < tL.length; j++) {
     * System.out.print(tL[i][j] + " ");
     * }
     * System.out.println();
     * }
     * System.out.println("valores: " + p + " " + r + " " + t);
     */
    if (r == 0 && t == 0 && p > pM) {
      return p;
    }
    if (r > 0) {
      for (int i = 0; i < tL.length; i++) {
        for (int j = 0; j < tL.length; j++) {
          if (sePuede(1, tL, i, j)) {
            tL[i][j] = 1;
            pM = estopa(T, r - 1, t, tL, pM, p + T[i][j]);
            tL[i][j] = 0;
          }
        }
      }
    }
    if (t > 0) {
      for (int i = 0; i < tL.length; i++) {
        for (int j = 0; j < tL.length; j++) {
          if (sePuede(2, tL, i, j)) {
            tL[i][j] = 2;
            pM = estopa(T, r, t - 1, tL, pM, p + T[i][j]);
            tL[i][j] = 0;
          }
        }
      }
    }
    return pM;
  }

  public static boolean sePuede(int x, int tLL[][], int tLLi, int tLLj) {

    for (int i = 0; i < tLL.length; i++) {

      if (tLL[i][tLLj] != 0) {
        return false;
      }
    }
    for (int j = 0; j < tLL.length; j++) {
      if (tLL[tLLi][j] != 0) {
        return false;
      }
    }
    for (int i = 0; i < tLL.length; i++) {
      for (int j = 0; j < tLL.length; j++) {
        if (Math.abs(tLLi - i) == Math.abs(tLLj - j) && !(tLLi == i && tLLj == j)) {
          if (tLL[i][j] == 1 || (tLL[i][j] == 2 && x == 1)) {
            return false;
          }
        }
      }
    }
    return true;
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String line;

    while ((line = br.readLine()) != null) {
      line = line.trim();
      if (line.isEmpty())
        continue;

      StringTokenizer st = new StringTokenizer(line);
      int Q = Integer.parseInt(st.nextToken());
      int R = Integer.parseInt(st.nextToken());

      int N = Q + R;

      int[][] tablero = new int[N][N];
      int[][] tablerolleno = new int[N][N];

      for (int i = 0; i < N; i++) {
        st = new StringTokenizer(br.readLine());
        for (int j = 0; j < N; j++) {
          tablero[i][j] = Integer.parseInt(st.nextToken());
          tablerolleno[i][j] = 0;
        }
      }

      System.out.println(estopa(tablero, Q, R, tablerolleno, 0, 0));
    }
  }
}
