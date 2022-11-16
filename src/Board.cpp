#include "stdafx.h"
#include "Board.h"

void Board::initVariables()
{


}

void Board::initCheckersOnPosition()
{
    
}

void Board::initPositions()
{
    int j = 1;
    int k = 24;
    int i = 57;

    while (i > 34)
    {
        i -= 4;
        this->positions[j] = i;
        this->positions[k] = i;
        k--;
        j++;
    }

    i = 27;
    while (i > 0 && j < 13)
    {
        i -= 4;
        this->positions[j] = i;
        this->positions[k] = i;
        k--;
        j++;
    }

}

Board::Board(std::vector<Checker*> checkersBlack, std::vector<Checker*> checkersWhite)
{
    //this->initVariables();
    this->checkersBlack = checkersBlack;
    this->checkersWhite = checkersWhite;  
    this->blackPhase = STANDARD;
    this->whitePhase = STANDARD;

    this->initPositions();
}

Board::Board(const Board* board)
{
    this->table = board->table;
    this->positions = board->positions;
    this->blackPhase = board->blackPhase;
    this->whitePhase = board->whitePhase;

    for (auto i : board->checkersOnPosition)
    {
        for (auto j : i.second)
        {
            //std::cout << "Push_Back: " << j->getId() << " Pos: " << j->getPosition() << "\n";
            this->checkersOnPosition[i.first].push_back(new Checker(j));
        }
    }

    //std::cout << "----------------------------------------------" << "\n";

    for (auto i : this->checkersOnPosition)
    {
        for (auto j : i.second)
        {
            if (j->getColor() == WHITE)
            {
                this->checkersWhite.push_back(j);
            }
            else
            {
                this->checkersBlack.push_back(j);
            }
        }
    }

    this->lastMove = board->lastMove;
    this->moveChecker = board->moveChecker;

}

Board::~Board()
{
    for (auto i : this->checkersBlack)
    {
        delete i;
    }

    for (auto i : this->checkersWhite)
    {
        delete i;
    }

    for (auto i : this->checkersOnPosition)
    {
        for (auto j : i.second)
        {
            delete j;
        }
    }

    delete this->lastMove;

}

void Board::createTable()
{
    this->table.push_back("_________________________________________________________");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("| 13  14  15  16  17  18  |   | 19  20  21  22  23  24  |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |BAR|                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("|                         |   |                         |");
    this->table.push_back("| 12  11  10   9   8   7  |   |  6   5   4   3   2   1  |");
    this->table.push_back("|_________________________|___|_________________________|");

    
}

void Board::makeMove(Move* move, Board* board)
{
    board->moveChecker = true;
    board->lastMove = move;

    //Checker* checker = ;
    // Updates the checker position in checker objects
    if (!board->checkersOnPosition.empty())
    {

        if (!board->checkersOnPosition[move->getFromPosition()].empty())
        {
            board->checkersOnPosition[move->getFromPosition()].back()->setPosition(move->getToPosition()); // updates checker position
        }

        if (move->getFromPosition_1() != -1)
        {
            if (!board->checkersOnPosition[move->getFromPosition_1()].empty() && move->getFromPosition_1() != move->getFromPosition())
            {
                board->checkersOnPosition[move->getFromPosition_1()].back()->setPosition(move->getToPosition_1());
                // updates second checker position not in the same col with the first position
            }
            if (board->checkersOnPosition[move->getFromPosition_1()].size() >= 2 && move->getFromPosition_1() == move->getFromPosition())
            {
                if (!board->checkersOnPosition[move->getFromPosition_1()].empty())
                {
                    board->checkersOnPosition[move->getFromPosition_1()].at(board->checkersOnPosition[move->getFromPosition_1()].size() - 2)->setPosition(move->getToPosition_1());
                }
            }
            
        }
    }
    
    //this->checkersOnPosition[move->getToPosition()].push_back(this->checkersOnPosition[move->getFromPosition()].back());
    //this->checkersOnPosition[move->getToPosition()].push_back(this->checkersOnPosition[move->getFromPosition()].back());
}

/// <summary>
/// 
/// </summary>
/// <param name="turn"> to check if this checker in the moe is at the top of the stack in a position</param>
/// <param name="dice"> the dice now must check his variables</param>
/// <param name="move"> we must check this move</param>
/// <returns></returns>
bool Board::isValidMove(Move* move, Dice* dice, int turn)
{
    if (this->checkersOnPosition[move->getFromPosition()].empty())
    {
        return false;
    }
    else
    {
        if (this->checkersOnPosition[move->getFromPosition()].back()->getColor() != turn)
        {
            return false;
        }
    }

    //We must check also for the number of moves if there right according to the indexes of the dices

    if (std::abs(move->getFromPosition() - move->getToPosition()) == dice->getDice1() + dice->getDice2())
    {
        dice->setPlayedDice1(true);
        dice->setPlayedDice2(true);
    }
    else if (std::abs(move->getFromPosition() - move->getToPosition()) == dice->getDice1() && !dice->getPlayedDice1())
    {
        dice->setPlayedDice1(true);
    }
    else if (std::abs(move->getFromPosition() - move->getToPosition()) == dice->getDice2() && !dice->getPlayedDice2())
    {
        dice->setPlayedDice2(true);
    }
    else
    {
        return false;
    }


    return true;
}

void Board::updateCheckersOnPosition()
{
    /*for (auto i : this->checkersBlack)
    {
        this->checkersOnPosition[i->getPosition()].push_back(i);
    }
    
    for (auto i : this->checkersWhite)
    {
        this->checkersOnPosition[i->getPosition()].push_back(i);
    }*/
}

void Board::updateCheckers(int color, Board* board)
{
    std::vector<Checker*> checkers;
    if (color == WHITE)
    {
        checkers = board->checkersWhite;
    }
    else
    {
        checkers = board->checkersBlack;
    }

    int checkerID = -1;
    int checkerID_1 = -1;

    if (board->lastMove && board->getLastMove()->getFromPosition() != -1)
    {
        if (board->getLastMove()->getFromPosition() == board->getLastMove()->getFromPosition_1())
        {
            checkerID = board->checkersOnPosition[board->getLastMove()->getFromPosition()].back()->getId();

            checkerID_1 = board->checkersOnPosition[board->getLastMove()->getFromPosition_1()][board->checkersOnPosition[board->getLastMove()->getFromPosition_1()].size() - 2]->getId();
        }
        else
        {
            checkerID = board->checkersOnPosition[board->getLastMove()->getFromPosition()].back()->getId();

            if (board->getLastMove()->getFromPosition_1() != -1)
            {
                checkerID_1 = board->checkersOnPosition[board->getLastMove()->getFromPosition_1()].back()->getId();
            }
        }
    }

    int test = 0;

    for (auto i : checkers)
    {
        bool already_on_position = false;

        // search for the checker -> if it is on position skip ...
        for (auto j : board->checkersOnPosition[i->getPosition()])
        {
            //if (i->getPosition() == j->getPosition())
            if (i == j)
            {// search if the checker is in the old position
                already_on_position = true;
                break;
            }
        }

        if (board->checkersOnPosition[i->getPosition()].size() == 2 && board->checkersOnPosition[i->getPosition()][0]->getColor() == board->checkersOnPosition[i->getPosition()][1]->getColor() && board->checkersOnPosition[i->getPosition()][0]->getId() == board->checkersOnPosition[i->getPosition()][1]->getId())
        {
            std::cout << "hey update" << "\n";
        }

        if (!already_on_position)
        {
            if (board->getColorPhase(color) == BEAR_OFF && (i->getPosition() == 25 || i->getPosition() == 0))
            {
                board->checkersOnPosition[i->getPosition()].push_back(i);
            }
            else
            {
                size_t size = board->checkersOnPosition[i->getPosition()].size();
                size_t size_table_item = board->checkersOnPosition[i->getPosition()].size();

                if (size < 6)
                {
                    if (i->getPosition() < 13)
                    {
                        int table_item = 15 - size_table_item;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        //std::cout << "Push: " << i->getId() << " Position: " << i->getPosition() << "\n";
                        board->table[table_item].replace(board->positions[i->getPosition()], 1, i->render());
                        test++;
                    }
                    else
                    {
                        int table_item = 3 + size_table_item;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        //std::cout << "Push: " << i->getId() << " Position: " << i->getPosition() << "\n";
                        board->table[table_item].replace(board->positions[i->getPosition()], 1, i->render());
                        test++;
                    }
                }
                else if (size < 12)
                {
                    size_table_item -= 6;
                    if (i->getPosition() < 13)
                    {
                        int table_item = 15 - size_table_item;
                        int table_position = board->positions[i->getPosition()] + 1;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        //std::cout << "Push: " << i->getId() << " Position: " << i->getPosition() << "\n";
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                    else
                    {
                        int table_item = 3 + size_table_item;
                        int table_position = board->positions[i->getPosition()] + 1;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        //std::cout << "Push: " << i->getId() << " Position: " << i->getPosition() << "\n";
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                }
                else if (size < 17)
                {
                    size_table_item -= 12;
                    if (i->getPosition() < 13)
                    {
                        int table_item = 15 - size_table_item;
                        int table_position = board->positions[i->getPosition()] + 2;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        //std::cout << "Push: " << i->getId() << " Position: " << i->getPosition() << "\n";
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                    else
                    {
                        int table_item = 3 + size_table_item;
                        int table_position = board->positions[i->getPosition()] + 2;
                        board->checkersOnPosition[i->getPosition()].push_back(i);
                        //std::cout << "Push: " << i->getId() << " Position: " << i->getPosition() << "\n";
                        board->table[table_item].replace(table_position, 1, i->render());
                        test++;
                    }
                }

            }

            if (test > 2)
            {
                std::cout << "test > 2" << "\n";
            }

            /*this->printTable();
            system("pause");*/
        }
    }


    if (board->moveChecker)
    {
        board->moveChecker = false;

        size_t size = board->checkersOnPosition[board->lastMove->getFromPosition()].size();
        size_t size_table_item = board->checkersOnPosition[board->lastMove->getFromPosition()].size();

        if (size <= 6)
        {
            size_table_item -= 1;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int count = 0;

                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(board->positions[board->lastMove->getFromPosition()], 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(board->positions[board->lastMove->getFromPosition()], 1, " ");
            }
        }
        else if (size <= 12)
        {
            size_table_item -= 7;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 1;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 1;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
        }
        else if (size < 17)
        {
            size_table_item -= 13;
            if (board->lastMove->getFromPosition() < 13)
            {
                int table_item = 15 - size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 2;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
            else
            {
                int table_item = 3 + size_table_item;
                int table_position = board->positions[board->lastMove->getFromPosition()] + 2;
                board->checkersOnPosition[board->lastMove->getFromPosition()].erase(board->checkersOnPosition[board->lastMove->getFromPosition()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition()], checkerID, color));
                board->table[table_item].replace(table_position, 1, " ");
            }
        }

        if (board->lastMove->getFromPosition_1() != -1)
        {
            size_t size_1 = board->checkersOnPosition[board->lastMove->getFromPosition_1()].size();
            size_t size_table_item_1 = board->checkersOnPosition[board->lastMove->getFromPosition_1()].size();

            if (size_1 <= 6)
            {
                size_table_item_1 -= 1;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(board->positions[board->lastMove->getFromPosition_1()], 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(board->positions[board->lastMove->getFromPosition_1()], 1, " ");
                }
            }
            else if (size_1 <= 12)
            {
                size_table_item_1 -= 7;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 1;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
            }
            else if (size_1 < 17)
            {
                size_table_item_1 -= 13;
                if (board->lastMove->getFromPosition_1() < 13)
                {
                    int table_item_1 = 15 - size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 2;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
                else
                {
                    int table_item_1 = 3 + size_table_item_1;
                    int table_position_1 = board->positions[board->lastMove->getFromPosition_1()] + 2;
                    board->checkersOnPosition[board->lastMove->getFromPosition_1()].erase(board->checkersOnPosition[board->lastMove->getFromPosition_1()].begin() + this->searchForID(board->checkersOnPosition[board->lastMove->getFromPosition_1()], checkerID_1, color));
                    board->table[table_item_1].replace(table_position_1, 1, " ");
                }
            }
            checkerID = -1;
            checkerID_1 = -1;
        }
    }
}

void Board::printTable()
{
    for (auto i : this->table)
    {
        std::cout << i << "\n";
    }
}

bool Board::getMoveChecker()
{
    return this->moveChecker;
}

Move* Board::getLastMove()
{
    return this->lastMove;
}

bool Board::canCheckerMove(Checker* checker)
{
    //int pos = checker->getPosition();
    //if (this->checkersOnPosition[pos].back()->getColor() == checker->getColor() && this->checkersOnPosition[pos].back()->getId() == checker->getId())
    
    if (checker->getPosition() != 25 && checker->getPosition() != 0)
    {
        if (!this->checkersOnPosition[checker->getPosition()].empty())
        {
            if (this->checkersOnPosition[checker->getPosition()].back() == checker)
            {// checking if the given checker is at the top of the column, and is the same color as the one at the top of the color
                return true;
            }
        }
    }
    
    return false;
}

bool Board::canSecondCheckerMove(Checker* checker)
{
    if (this->checkersOnPosition[checker->getPosition()].size() >= 2)
    {
        if (this->checkersOnPosition[checker->getPosition()].at(this->checkersOnPosition[checker->getPosition()].size() - 2) == checker)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

std::vector<Board*> Board::getChildren(int color, Dice* dice, Board* board)
{
    std::vector<Board*> children;
    bool one_dice_cannot_be_played = true;
    
    int from_multiple_pos1;
    int from_multiple_pos2;

    if (color == WHITE)
    {
        from_multiple_pos1 = -1 * (dice->getDice1());
        from_multiple_pos2 = -1 * (dice->getDice2());
    }
    else
    {
        from_multiple_pos1 = dice->getDice1();
        from_multiple_pos2 = dice->getDice2();
    }
    
    for (auto i : board->getCheckers(color))
    {
        if (this->canCheckerMove(i))
        {

        }
    }










    //-------------------------------------------------------------------------------------------
    std::vector<Board*> children;
    bool one_dice_cannot_be_played = true;

    //first we check if the two dice are not the same
    if (true) //dice->getDice1() != dice->getDice2())
    {
        int from_multiple_pos;// it will tell us if we are white, then we must go backwards

        int from_multiple_pos1;
        int from_multiple_pos2;

        if (color == WHITE)
        {
            from_multiple_pos = -1 * (dice->getDice1() + dice->getDice2());

            from_multiple_pos1 = -1 * (dice->getDice1());
            from_multiple_pos2 = -1 * (dice->getDice2());
        }
        else
        {
            from_multiple_pos = dice->getDice1() + dice->getDice2();

            from_multiple_pos1 = dice->getDice1();
            from_multiple_pos2 = dice->getDice2();
        }

        // In this first case ,we check if the checker can move the sum(dice1,dice2)
        for (auto i : board->getCheckers(color))
        {
            if (this->canCheckerMove(i))
            {
                if (this->isValidMoveAI(i->getPosition() + from_multiple_pos, i))
                {
                    Board* child = new Board(board);
                    
                    Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos);
                    this->makeMove(move, child);
                    this->updateCheckers(color, child);
                    //std::cout << "Double from pos: " << move->getFromPosition() << " Double to pos: " << move->getToPosition() << "ID 1st checker" << i->getId() << std::endl;
                    //std::cout << "Double from pos 1: " << move->getFromPosition_1() << " Double to pos 1 : " << move->getToPosition_1() << std::endl;
                    children.push_back(child);
                    one_dice_cannot_be_played = false;
                }

                //In this second case, we search for the most possible moves that the checker can do
                /*
                * 1.We search for every possible combination of two checkers with the two different indexes of the dices
                * 2.We must search the case where he cannot make use of one of the two checkers.That's the case of the one_dice_cannot_be_played
                */

                for (auto j : board->getCheckers(color))
                {
                    if (j != i)
                    {
                        bool check;
                        if (i->getPosition() == j->getPosition())
                        {
                            check = this->canSecondCheckerMove(j);
                        }
                        else
                        {
                            check = this->canCheckerMove(j);
                        }

                        if (check) // checks if j is under i
                        {
                            if (i->getPosition() == j->getPosition() && board->checkersOnPosition[i->getPosition()].size() < 2)
                            {
                                std::cout << "here " << std::endl;
                                //std::cout << " ID 1 :" << i->getId() << " ID 2 :" << j->getId() << std::endl;
                            }
                            // now we check if the two dices can make use of the index of the dice
                            if (this->isValidMoveAI(i->getPosition() + from_multiple_pos1, i) && this->isValidMoveAI(j->getPosition() + from_multiple_pos2, j))
                            {
                                //Here the bot can play the two checkers with the first checker follows the index of the second dice and vice versa

                                Board* child = new Board(board);
                                Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos1);
                                move->setFromPosition_1(j->getPosition());
                                move->setToPosition_1(j->getPosition() + from_multiple_pos2);
                                this->makeMove(move, child);

                                // TO DO: updateCheckers -> need to update for setPosition_1 ...
                                this->updateCheckers(color, child);
                                //std::cout << "ID 1st checker " << i->getId() << "ID 2nd checker " << j->getId() << std::endl;
                                //std::cout << "A from pos: " << move->getFromPosition() << " A to pos: " << move->getToPosition() << std::endl;
                                //std::cout << "A from pos 1: " << move->getFromPosition_1() << " A to pos 1 : " << move->getToPosition_1() << std::endl;
                                children.push_back(child);
                                one_dice_cannot_be_played = false;
                            }

                            if (this->isValidMoveAI(i->getPosition() + from_multiple_pos2, i) && this->isValidMoveAI(j->getPosition() + from_multiple_pos1, j))
                            {
                                //Here the bot can play the two checkers with the first checker follows the index of the second dice and vice versa

                                Board* child = new Board(board);
                                Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos2);
                                move->setFromPosition_1(j->getPosition());
                                move->setToPosition_1(j->getPosition() + from_multiple_pos1);
                                this->makeMove(move, child);

                                // TO DO: updateCheckers -> need to update for setPosition_1 ...
                                this->updateCheckers(color, child);
                                //std::cout << "ID 1st checker " << i->getId() << "ID 2nd checker " << j->getId() << std::endl;
                                //std::cout << "B from pos: " << move->getFromPosition() << " B to pos: " << move->getToPosition() << std::endl;
                                //std::cout << "B from pos 1: " << move->getFromPosition_1() << " B to pos 1 : " << move->getToPosition_1() << std::endl;
                                children.push_back(child);
                                one_dice_cannot_be_played = false;
                            }
                        }
                    }
                }
            }
        }

        if (one_dice_cannot_be_played)
        {
            // here we play only one of the two dice
            for (auto i : board->getCheckers(color))
            {
                /*
                * Check if the checker can play the 1st dice
                */
                if (this->canCheckerMove(i))
                {
                    if (this->isValidMoveAI(i->getPosition() + from_multiple_pos1, i))
                    {
                        Board* child = new Board(this);
                        Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos1);
                        this->makeMove(move, child);
                        this->updateCheckers(color, child);
                        children.push_back(child);
                    }

                    /*
                    * Check if the checker can play the 2nd dice
                    */
                    if (this->isValidMoveAI(i->getPosition() + from_multiple_pos2, i))
                    {
                        Board* child = new Board(this);
                        Move* move = new Move(i->getPosition(), i->getPosition() + from_multiple_pos2);
                        this->makeMove(move, child);
                        this->updateCheckers(color, child);
                        children.push_back(child);
                    }
                }
                
            }
        }
    }

    return children;
}

bool Board::isValidMoveAI(int position, Checker* checker)
{
    if (isValidToPosition(position, checker))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::isValidToPosition(int position, Checker* checker)
{
    if (position < 1 || position > 24)
    {
        return false;
    }
    // first check if the position doesn't have any checkers
    if (this->checkersOnPosition[position].empty())
    {
        return true;
    }
    else if (this->checkersOnPosition[position].back()->getColor() == checker->getColor())
    {// here we have the top checker of the column with the same color of the checker that we want to move
        return true;
    }
    else if (this->checkersOnPosition[position].size() == 1)
    {// here we have only one checker with different color in the to_position column. So we "eat" it
        return true;
    }
    else
    {// here we have a lot of checkers with the opposite color in the same row
        return false;
    }
}

std::vector<Checker*> Board::getCheckers(int color)
{
    if (color == WHITE)
    {
        return this->checkersWhite;
    }
    else
    {
        return this->checkersBlack;
    }
}

std::map<int, std::vector<Checker*>> Board::getCheckersOnPosition()
{
    return this->checkersOnPosition;
}

int Board::searchForID(std::vector<Checker*> checkers, int id, int color)
{
    int count = 0;
    for (auto i : checkers)
    {
        if (i->getId() == id && i->getColor() == color)
        {
            return count;
        }
        count++;
    }
    return -1;
}

int Board::getColorPhase(int color)
{
    if (color == BLACK)
    {
        return this->blackPhase;
    }
    else
    {
        return this->whitePhase;
    }
}


bool Board::isTerminal()
{
    /*bool is_this_the_end = true;
    for (auto i : this->checkersBlack)
    {
        if (i->getPosition() != 0)
        {
            is_this_the_end = false;
        }
    }

    for (auto i : this->checkersWhite)
    {
        if (i->getPosition() != 25)
        {
            is_this_the_end = true;
        }
    }
    return is_this_the_end;*/
    return false;
}

