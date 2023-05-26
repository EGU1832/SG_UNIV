/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/

	#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();
		void DrawRoundLine(int x1, int y1, int x2, int y2, int LineWidth);

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool readFile();
		void freeMemory();
		bool DFS();
		void dfsdraw();
		int HEIGHT;		// 미로의 높이
		int WIDTH;		// 미로의 너비
		char** input;	// 입력 받은 미로를 저장하는 배열
		int** visited;	// 방문 여부를 저장하는 배열
		int maze_col;	// 미로의 열 개수
		int maze_row;	// 미로의 행 개수
		int k;
		int isOpen;		// 출구가 열려있는지 여부를 저장하는 변수. 0이면 닫혀있고 1이면 열려있다.
		int isDFS;		// DFS 탐색을 실행할지 여부를 저장하는 변수. 0이면 실행하지 않고 1이면 실행한다.
		int isBFS;		// BFS 탐색을 실행할지 여부를 저장하는 변수. 0이면 실행하지 않고 1이면 실행한다.

		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		bool isdfs;
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);

};
