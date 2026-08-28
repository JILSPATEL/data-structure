class Solution {
public:
    int N;
    bool isValid(vector<string>& board, int row, int col) {

        for (int i = row - 1; i >= 0; i--)
            if (board[i][col] == 'Q')
                return false;

        for (int i = row - 1, j = col - 1;
             i >= 0 && j >= 0;
             i--, j--)
            if (board[i][j] == 'Q')
                return false;

        for (int i = row - 1, j = col + 1;
             i >= 0 && j < N;
             i--, j++)
            if (board[i][j] == 'Q')
                return false;

        return true;
    }

    int solve(vector<string> &board,int row){
        if(row==N) return 1;
        int ways=0;

        for(int col=0;col<N;col++){
            if(isValid(board,row,col)){
                board[row][col]='Q';
                ways+=solve(board,row+1);
                board[row][col]='.';
            }
        }
        return ways;
    }
    int totalNQueens(int n) {
        N=n;
        vector<string> board(n, string(n, '.'));
        return solve(board,0);
    }
};