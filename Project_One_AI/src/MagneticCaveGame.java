import java.util.Scanner;

public class MagneticCaveGame {
    private static final int BOARD_SIZE = 8; //define the Board size
    private static final char PLAYER_1 = '■';
    private static final char PLAYER_2= '□';

    private char[][] board;
    private boolean isPlayer1Turn;

    public MagneticCaveGame() {
        board = new char[BOARD_SIZE][BOARD_SIZE]; // Create a new game board
        initializeBoard();  // Initialize the game board with empty cells
    }

    private void initializeBoard() {  //Initializes the game board with empty cells
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = '-';
            }
        }
    }

    public void playGame() {
        Scanner scanner = new Scanner(System.in);
        isPlayer1Turn = true;

        boolean manualModePlayer1 = true;
        boolean manualModePlayer2 = true;

        System.out.println("Select mode of play for Player 1 (■):");
        System.out.println("1. Manual");
        System.out.println("2. Automatic");
        int modePlayer1 = scanner.nextInt();
        scanner.nextLine();

        switch (modePlayer1) {  // Validate and set Player 1's play mode
            case 1:
                manualModePlayer1 = true;
                break;
            case 2:
                manualModePlayer1 = false;
                break;
            default:
                System.out.println("Invalid mode selection,please select 1 or 2 ");
                System.out.println("Select mode of play for Player 1 (■):");
                System.out.println("1. Manual");
                System.out.println("2. Automatic");
                modePlayer1 = scanner.nextInt();
                scanner.nextLine();
                manualModePlayer1 = true;
                break;
        }

        System.out.println("Select mode of play for Player 2 (□):");
        System.out.println("1. Manual");
        System.out.println("2. Automatic");
        int modePlayer2 = scanner.nextInt();
        scanner.nextLine();

        switch (modePlayer2) {  // Validate and set Player 2's play mode
            case 1:
                manualModePlayer2 = true;
                break;
            case 2:
                manualModePlayer2 = false;
                break;
            default:
                System.out.println("Invalid mode selection");
                System.out.println("Invalid mode selection,please select 1 or 2 ");
                System.out.println("Select mode of play for Player 2 (□):");
                System.out.println("1. Manual");
                System.out.println("2. Automatic");
                modePlayer1 = scanner.nextInt();
                scanner.nextLine();
                manualModePlayer2 = true;
                break;
        }

        while (true) {
            printBoard();

            if (isPlayer1Turn) {
                System.out.println("Player 1's turn (■)");
                if (manualModePlayer1) {
                    makeManualMove(scanner);
                } else {
                    makeAutomaticMove();
                }
            } else {
                System.out.println("Player 2's turn (□)");
                if (manualModePlayer2) {
                    makeManualMove(scanner);
                } else {
                    makeAutomaticMove();
                }
            }

            if (checkWhoWin()) {
                printBoard();


                if (isPlayer1Turn) {
                    System.out.println("Player 1 is wins");
                } else {
                    System.out.println("Player 2 is wins");
                }

                break;
            }

            isPlayer1Turn = !isPlayer1Turn;
        }
    }

    private void makeManualMove(Scanner scanner) {
        String move;

        while (true) {
            System.out.print("Enter your move: (example: A1)"); // Prompt the player to enter their move
            move = scanner.nextLine(); // Read the input from the player

            if (isValidMove(move)) { // Check if the move is valid
                makeMove(move); // Make the move if it is valid
                break; // Exit the loop
            } else {
                System.out.println("Invalid move. Please try again."); // Display an error message for an invalid move
            }
        }
    }

    private boolean isValidMove(String move) {
        if (move.length() != 2) {
            return false;
        }


        char colChar = Character.toUpperCase(move.charAt(0));
        char rowChar = move.charAt(1);

        // Validate column value
        if (colChar < 'A' || colChar >= 'A' + BOARD_SIZE) {
            return false;
        }

        // Validate row value
        if (rowChar < '1' || rowChar >= '1' + BOARD_SIZE) {
            return false;
        }

        // Convert column and row characters to indices
        int col = colChar - 'A';
        int row = rowChar - '1';

        // Check if the specified cell is empty and within the valid move positions
        return board[row][col] == '-' && isValidMovePosition(row, col);
    }

    private boolean isValidMovePosition(int row, int col) {
        if (row == 0 || row == BOARD_SIZE - 1) {
            return true; // Valid move position if it is on the top or bottom row
        }

        // Valid move position if it is stacked on top of another brick
        return board[row - 1][col] != '-' || board[row + 1][col] != '-';
    }

    private void makeMove(String move) {
        char PLAYER_1 = '■';
        char PLAYER_2 = '□';
        char colChar = Character.toUpperCase(move.charAt(0));
        char rowChar = move.charAt(1);

        int col = colChar - 'A';
        int row = rowChar - '1';

        board[row][col] = isPlayer1Turn ? PLAYER_1 : PLAYER_2;
    }
    private boolean checkWhoWin() {
        // Check for 5 bricks horizontally
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE - 4; j++) {
                if (board[i][j] != '-' &&
                        board[i][j] == board[i][j + 1] &&
                        board[i][j] == board[i][j + 2] &&
                        board[i][j] == board[i][j + 3] &&
                        board[i][j] == board[i][j + 4]) {
                    return true; // horizontal win condition met
                }
            }
        }

        // Check for 5  bricks vertically
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int i = 0; i < BOARD_SIZE - 4; i++) {
                if (board[i][j] != '-' &&
                        board[i][j] == board[i + 1][j] &&
                        board[i][j] == board[i + 2][j] &&
                        board[i][j] == board[i + 3][j] &&
                        board[i][j] == board[i + 4][j]) {
                    return true; //vertical win condition met
                }
            }
        }

        // Check for 5  bricks diagonally
        for (int i = 0; i < BOARD_SIZE - 4; i++) {
            for (int j = 0; j < BOARD_SIZE - 4; j++) {
                if (board[i][j] != '-' &&
                        board[i][j] == board[i + 1][j + 1] &&
                        board[i][j] == board[i + 2][j + 2] &&
                        board[i][j] == board[i + 3][j + 3] &&
                        board[i][j] == board[i + 4][j + 4]) {
                    return true; // diagonal win condition met
                }

                if (board[i][j + 4] != '-' &&
                        board[i][j + 4] == board[i + 1][j + 3] &&
                        board[i][j + 4] == board[i + 2][j + 2] &&
                        board[i][j + 4] == board[i + 3][j + 1] &&
                        board[i][j + 4] == board[i + 4][j]) {
                    return true; // diagonal win condition met
                }
            }
        }

        return false; // No win condition found
    }


    private void makeAutomaticMove() {
        long startTime = System.currentTimeMillis();
        long endTime = startTime + 3000; // 3 seconds

        int bestScore = Integer.MIN_VALUE;
        int bestRow = -1;
        int bestCol = -1;

        // Iterate over each cell on the board
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == '-') {
                    // Try making a move in the current cell
                    board[i][j] = isPlayer1Turn ? PLAYER_1 : PLAYER_2;

                    // Perform the minimax algorithm to evaluate the move
                    int score = minimax(board, 0, false, Integer.MIN_VALUE, Integer.MAX_VALUE, endTime);


                    board[i][j] = '-';

                    // Update the best score and corresponding row and column
                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }

        // Check if a best move was found
        if (bestRow != -1 && bestCol != -1) {
            // Convert the best row and column to corresponding characters
            char colChar = (char) ('A' + bestCol);
            char rowChar = (char) ('1' + bestRow);


            String move = "" + colChar + rowChar;


            makeMove(move);
        }
    }

    private int minimax(char[][] board, int depth, boolean isMaximizingPlayer, int alpha, int beta, long endTime) {
        // Check if the termination condition is met
        if (System.currentTimeMillis() >= endTime || depth >= 5) {
            return evaluateBoard(board);
        }

        if (isMaximizingPlayer) {
            int maxScore = Integer.MIN_VALUE;

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] == '-') {

                        board[i][j] = PLAYER_1;
                        int score = minimax(board, depth + 1, false, alpha, beta, endTime);
                        board[i][j] = '-';

                        // Update the maximum score and alpha
                        maxScore = Math.max(maxScore, score);
                        alpha = Math.max(alpha, score);

                        // Perform alpha-beta pruning
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
            }

            return maxScore;
        } else {
            int minScore = Integer.MAX_VALUE;

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] == '-') {
                        // Try a possible move for the minimizing player
                        board[i][j] = PLAYER_2;
                        int score = minimax(board, depth + 1, true, alpha, beta, endTime);
                        board[i][j] = '-';

                        // Update the minimum score and beta
                        minScore = Math.min(minScore, score);
                        beta = Math.min(beta, score);

                        // Perform alpha-beta pruning
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
            }

            return minScore;
        }
    }

    private int evaluateBoard(char[][] board) {
        // Calculate the number of possible bridges for each player
        int scorePlayer1 = countPossibleBridges(board, PLAYER_1);
        int scorePlayer2 = countPossibleBridges(board, PLAYER_2);

        if (scorePlayer1 >= 5) {
            return Integer.MAX_VALUE; // Player 1 wins
        } else if (scorePlayer2 >= 5) {
            return Integer.MIN_VALUE; // Player 2 wins
        } else {
            return scorePlayer1 - scorePlayer2; // Difference in possible bridges
        }
    }


    private int countPossibleBridges(char[][] board, char playerBrick) {
        int count = 0;

        // Check rows for possible bridges
        for (int row = 0; row < BOARD_SIZE; row++) {
            int consecutiveBricks = 0;
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (board[row][col] == playerBrick) {
                    consecutiveBricks++;
                    if (consecutiveBricks == 5) {
                        return 5; // Player can form a bridge, return maximum score
                    }
                } else {
                    consecutiveBricks = 0;
                }
            }
            count += consecutiveBricks;
        }

        // Check columns for possible bridges
        for (int col = 0; col < BOARD_SIZE; col++) {
            int consecutiveBricks = 0;
            for (int row = 0; row < BOARD_SIZE; row++) {
                if (board[row][col] == playerBrick) {
                    consecutiveBricks++;
                    if (consecutiveBricks == 5) {
                        return 5; // Player can form a bridge, return maximum score
                    }
                } else {
                    consecutiveBricks = 0;
                }
            }
            count += consecutiveBricks;
        }

        // Check diagonals for possible bridges (top-left to bottom-right)
        for (int row = 0; row < BOARD_SIZE - 4; row++) {
            for (int col = 0; col < BOARD_SIZE - 4; col++) {
                int consecutiveBricks = 0;
                for (int i = 0; i < 5; i++) {
                    if (board[row + i][col + i] == playerBrick) {
                        consecutiveBricks++;
                        if (consecutiveBricks == 5) {
                            return 5; // Player can form a bridge, return maximum score
                        }
                    } else {
                        consecutiveBricks = 0;
                    }
                }
                count += consecutiveBricks;
            }
        }

        // Check diagonals for possible bridges (top-right to bottom-left)
        for (int row = 0; row < BOARD_SIZE - 4; row++) {
            for (int col = BOARD_SIZE - 1; col >= 4; col--) {
                int consecutiveBricks = 0;
                for (int i = 0; i < 5; i++) {
                    if (board[row + i][col - i] == playerBrick) {
                        consecutiveBricks++;
                        if (consecutiveBricks == 5) {
                            return 5; // Player can form a bridge, return maximum score
                        }
                    } else {
                        consecutiveBricks = 0;
                    }
                }
                count += consecutiveBricks;
            }
        }

        return count;
    }


    private void printBoard() {
        System.out.println(); // Print an empty line

        // Print column labels
        System.out.print("  ");
        for (char col = 'A'; col < 'A' + BOARD_SIZE; col++) {
            System.out.print(col + " ");
        }
        System.out.println(); // Print a new line after column labels

        // Print rows
        for (int row = 0; row < BOARD_SIZE; row++) {
            System.out.print(row + 1); // Print row number

            // Print cells and cell boundaries
            for (int col = 0; col < BOARD_SIZE; col++) {
                System.out.print("|" + board[row][col]);
            }
            System.out.print("|"); // Close the row with a final boundary
            System.out.println(); // Print a new line after each row

            if (row != BOARD_SIZE - 1) {
                // Print inner borders between rows
                System.out.print(" ");
                for (int col = 0; col < BOARD_SIZE; col++) {
                    System.out.print("--");
                }
                System.out.println(); // Print a new line after each inner border
            }
        }

        System.out.println(); // Print an empty line after the board
    }

    public static void main(String[] args) {
        MagneticCaveGame game = new MagneticCaveGame();
        game.playGame();
    }
}
