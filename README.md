# viktor-hater-bot
![GitHub build-test status](https://img.shields.io/github/workflow/status/sabotack/viktor-hater-bot/Makefile-build-test)
![Latest stable release](https://img.shields.io/github/v/release/sabotack/viktor-hater-bot?color=brightgreen&label=latest%20stable%20version)
![Current Version](https://img.shields.io/github/v/release/sabotack/viktor-hater-bot?include_prereleases&label=current%20version)
![Commits since latest release (including pre-releases)](https://img.shields.io/github/commits-since/sabotack/viktor-hater-bot/latest?include_prereleases)
![Repository size](https://img.shields.io/github/repo-size/sabotack/viktor-hater-bot)
![License](https://img.shields.io/github/license/sabotack/viktor-hater-bot)

## About

A discord bot written in C with the sole purpose of hating on Viktor (this bot is made for entertainment purposes only).
The bot listens for the word 'viktor' in all channels and responds with a roast/comment selected randomly from a predefined list.

This project was originally created during my free time in the break between my 1st and 2nd semester of Software Engineering at Aalborg University. 

The main point was to practice C-programming while discovering and learning an entire new framework for discord bot development (Concord).
Along with learning about Concord, I also got familiar with the Discord API and developer portal.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Getting started](#getting-started)
    - [Installation](#installation)
3. [Stability Levels](#stability-levels)
4. [License](#license)

## Prerequisites
- [git](https://git-scm.com/)
- [gcc](https://gcc.gnu.org/)
- [make](https://www.gnu.org/software/make/)
- [concord](https://github.com/Cogmasters/concord/)

## Getting started
### Installation

## Stability Levels
[#1 - #5]  
The stability levels are used to indicate program stability, where level #1 indicates least proven stability and level #5 indicates most stable release):

[In hours of continuous program runtime]
- #1: 12+ hours
- #2: 24+ hours
- #3: 48+ hours
- #4: 96+ hours
- #5: 168+ hours

\* To ignore SIGPIPE errors during runtime, manually disable SIGPIPE as follows:
```
(gdb) handle SIGPIPE nostop noprint pass
```

## License

Licensed under the [MIT](LICENSE) license.

