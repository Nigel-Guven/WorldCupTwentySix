
Simulations::Simulations() {}

void League::simulateClassicGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, int remainingPoints) {
    for (int i = 0; i < remainingPoints; ++i) {
        bool team1GetsPoint = std::rand() % 2 == 0;
        if (team1GetsPoint) {
            team1Points++;
        }
        else {
            team2Points++;
        }
    }
    finalizeMatchResult(homeTeam, awayTeam, team1Points, team2Points);
}

void League::simulateRandomGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points) {
    int homeWinChance = team1Points;
    int awayWinChance = 100 - team2Points;
    int drawChanceStart = team1Points + 1;

    int randomNumber = std::rand() % 100 + 1;

    if (randomNumber >= drawChanceStart && randomNumber <= team2Points) {
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
    else if (randomNumber <= homeWinChance) {
        homeTeam.addWin();
        awayTeam.addLoss();
    }
    else {
        awayTeam.addWin();
        homeTeam.addLoss();
    }
}

void League::simulateFirstTo50GameMode(Team& homeTeam, Team& awayTeam) {
    int homeTeamScore = 0, awayTeamScore = 0;

    while (homeTeamScore < 50 && awayTeamScore < 50) {
        bool team1GetsPoint = std::rand() % 2 == 0;
        if (team1GetsPoint) {
            homeTeamScore++;
        }
        else {
            awayTeamScore++;
        }
    }

    if (homeTeamScore >= 50 && (homeTeamScore - awayTeamScore > 4)) {
        homeTeam.addWin();
        awayTeam.addLoss();
    }
    else if (awayTeamScore >= 50 && (awayTeamScore - homeTeamScore > 4)) {
        awayTeam.addWin();
        homeTeam.addLoss();
    }
    else {
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
}

void League::simulateNegativeInfluenceGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points) {
    bool homeTeamInjury = std::rand() % 100 < 6;  // 6% chance for injury
    bool awayTeamInjury = std::rand() % 100 < 6;  // 6% chance for injury

    bool homeTeamRedCard = std::rand() % 100 < 7;  // 7% chance for red card
    bool awayTeamRedCard = std::rand() % 100 < 7;  // 7% chance for red card

    if (homeTeamInjury) {
        team1Points -= 3;
    }

    if (awayTeamInjury) {
        team2Points -= 3;
    }

    if (homeTeamRedCard) {
        team1Points -= 7;
    }

    if (awayTeamRedCard) {
        team2Points -= 7;
    }

    finalizeMatchResult(homeTeam, awayTeam, team1Points, team2Points);
}