import java.io.*;
import java.util.*;

public class tmp {
  static int mejorValor;
  static int N;

  static class Estado {
    boolean[] filaUsada;
    boolean[] colUsada;
    int[][] tablero;

    Estado(int n, int[][] tab) {
      filaUsada = new boolean[n];
      colUsada = new boolean[n];
      tablero = tab;
    }

    boolean diagonalLibre(int i, int j) {
      // Revisar todas las diagonales
      for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
          if (tablero[x][y] == -1) { // Hay una reina
            if (Math.abs(x - i) == Math.abs(y - j)) {
              return false;
            }
          }
        }
      }
      return true;
    }
  }

  static void backtrack(Estado estado, int queensRestantes, int towerRestantes, int valorActual) {
    // Caso base: colocamos todas las piezas
    if (queensRestantes == 0 && towerRestantes == 0) {
      mejorValor = Math.max(mejorValor, valorActual);
      return;
    }

    // Poda: si no podemos mejorar, retornar
    if (valorActual + (queensRestantes + towerRestantes) < mejorValor) {
      return;
    }

    // Intentar colocar pieza en cada posición
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (estado.filaUsada[i] || estado.colUsada[j])
          continue;

        int valor = estado.tablero[i][j];

        // Intentar colocar reina
        if (queensRestantes > 0 && estado.diagonalLibre(i, j)) {
          // Marcar posición
          estado.filaUsada[i] = true;
          estado.colUsada[j] = true;
          int temp = estado.tablero[i][j];
          estado.tablero[i][j] = -1;

          backtrack(estado, queensRestantes - 1, towerRestantes, valorActual + );

          // Desmarcar
          estado.filaUsada[i] = false;
          estado.colUsada[j] = false;
          estado.tablero[i][j] = temp;
        }

        // Intentar colocar torre
        if (towerRestantes > 0) {
          estado.filaUsada[i] = true;
          estado.colUsada[j] = true;

          backtrack(estado, queensRestantes, towerRestantes - 1, valorActual + valor);

          estado.filaUsada[i] = false;
          estado.colUsada[j] = false;
        }
      }
    }
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

      N = Q + R;
      int[][] tablero = new int[N][N];

      for (int i = 0; i < N; i++) {
        st = new StringTokenizer(br.readLine());
        for (int j = 0; j < N; j++) {
          tablero[i][j] = Integer.parseInt(st.nextToken());
        }
      }

      mejorValor = 0;
      Estado estado = new Estado(N, tablero);
      backtrack(estado, Q, R, 0);

      System.out.println(mejorValor);
    }
  }
}
