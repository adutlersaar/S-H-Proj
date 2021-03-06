#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
#include <stdio.h>

/**
* Calculating a node in the Minimax Tree
*
* @param currentGame - The current game state
* @param nodeDepth - The depth from this node in the miniMax algorithm
* @param imax - boolean set to true if need to maximize children score, false to minimize
* @return
* score of node in the Minmax Tree
*/
int spMinimaxNodeCalc(SPFiarGame* currentGame,
	unsigned int nodeDepth, bool imax) {
	int tempScore, finalScore;
	bool madeMove = false;
	char win;
	if (nodeDepth == 0)
	{
		return spMinimaxScoring(currentGame);
	}

	if ((win = spFiarCheckWinner(currentGame)) == SP_FIAR_GAME_PLAYER_1_SYMBOL)
	{
		return INT_MAX;
	}
	if (win == SP_FIAR_GAME_PLAYER_2_SYMBOL)
	{
		return INT_MIN;
	}

	for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if (spFiarGameIsValidMove(currentGame, i))
		{
			spFiarGameSetMove(currentGame, i);
			tempScore = spMinimaxNodeCalc(currentGame, nodeDepth - 1, !imax);
			spFiarGameUndoPrevMove(currentGame);
			if (!madeMove)
			{
				finalScore = tempScore;
				madeMove = !madeMove;
			}
			else
			{
				finalScore = imax ? MAX(finalScore, tempScore) : MIN(finalScore, tempScore);
			}
		}
	}
	if (!madeMove) {
		finalScore = spMinimaxScoring(currentGame);
	}
	return finalScore;
}
