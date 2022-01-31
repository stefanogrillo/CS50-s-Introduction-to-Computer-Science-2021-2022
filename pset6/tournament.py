# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage checking input length
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Read teams into memory from file
    teams = []
    filename = sys.argv[1]
    # Read the file
    with open(filename) as file:
        reader = csv.DictReader(file)
        # Add every "team" into the "teams"; transform strings in "rating" into integers
        for team in reader:
            teams += [team]
            team["rating"] = int(team["rating"])

    # Simulate N tournaments and keep track of win counts
    counts = {}
    # Loop N times the tournaments
    for i in range(N):
        winner = simulate_tournament(teams)
        # Increase the value of wins for the club if already inside "counts"
        if winner in counts:
            counts[winner] += 1
        # Add to "counts"
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")
