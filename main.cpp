#include "lib/framework.hpp"



int main() {
	AppEnv env(3000, 2048, false, true);

	//ゲームの素材（主人公）
	Texture anb_top("res/anb1.png");//正面
	Texture anb_side("res/anb2.png");//横
	Texture anb_back("res/anb3.png");//後ろ
	
	//素材その他
	Texture title("res/title_top.png");
	Texture title2("res/title2.png");
	Texture owari("res/owari.png");
	Texture door("res/door.png");
	Texture door2("res/door2.png");
	Texture titledoorhan("res/titledoorhan.png");
	Texture akari("res/akari.png");
	Texture hp("res/heart.png");
	Texture open("res/open.png");
	Texture closed("res/closed.png");
	Texture end("res/endcard.png");
	//音源
	Media nock("res/nock.wav");
	Media keyclose("res/keyclose.wav");
	//キャラの移動x,y
	int x = -1500;
	int y = -1024;

	
	//
	int stage_count = 0;
	
	int life = 3;
	int stage_clear=0;
	int block_x = 200;
	int block_y = 200;
	int akari_count = 0;
	int atari_count = 0;
	
	//stage_clear = 1;
	//**************************************おおもと**************************************
	while (true){

		env.begin();

		
		

		//::::::::::::::::::::::タイトル画面::::::::::::::::::::::::
		while (env.isOpen()) {
			env.begin();

			drawTextureBox(-1500, -1024, 3000, 2048, 0, 0, 4096, 2048, title);
			drawTextureBox(-1050, -600, 200, 200, 0, 0, 512, 512, open);
			drawTextureBox(100, -600, 200, 200, 0, 0, 512, 512, closed);

			if (!(-330 < x || -830 > x + 300 || -174 < y || -1024 > y + 600)){
				drawTextureBox(-828, -1010, 510, 840, 0, 0, 512, 512, titledoorhan);
				if (env.isPressKey(GLFW_KEY_SPACE)){
					x = -40;
					y = -1024;
					nock.play();
					
					break;
				}
			}



			//右ドア
			if (stage_clear == 1){
				drawTextureBox(100, -600, 200, 200, 0, 0, 512, 512, open);
				if (!(835 < x || 325 > x + 300 || -184 < y || -1024 > y + 600)){
					drawTextureBox(320, -1010, 510, 840, 0, 0, 512, 512, titledoorhan);
					
						if (env.isPressKey(GLFW_KEY_SPACE)){
							x = -40;
							y = -1024;
							nock.play();
							stage_count = 11;
							break;
							
					}

				}

			}
			else {
				
					if (env.isPushKey(GLFW_KEY_SPACE)){
						if (!(835 < x || 325 > x + 300 || -184 < y || -1024 > y + 600)){
						keyclose.play();
					}
				}
			}



			if (env.isPressKey(GLFW_KEY_LEFT)){
				x -= 5;
				drawTextureBox(x, y, 300, 600, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
				if (x <-1500){
					
					x = -1500;
				}

			}
			

				else if (env.isPressKey(GLFW_KEY_RIGHT)){
				x += 5;
				drawTextureBox(x, y, 300, 600, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
				if (x > 1200){
					x = 1200;
				}
			}
				else {
				drawTextureBox(x, y, 300, 600, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
			}

			//if(!( □+x<x ||　□x >x+300 ||　□+y <y ||　□y　> y+600))

			
			



			env.end();
		}


		//:::::::::::::::::::::::ゲーム本編:::::::::::::::::::::::::::

		while (env.isOpen()) {

			Vec2f pos = env.mousePosition();

			env.begin();
		
			//--------------------チュートリアル---------------------

			//背景
			
			if (stage_count == 0){
				drawFillBox(-1024, -1024, 2048, 2048, Color(1, 1, 1, 1));


			//ドア
				drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
				if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
					drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
					if (env.isPressKey(GLFW_KEY_SPACE)){
						stage_count++;
						x = -40;
						y = -1024;
						nock.play();
					}
				}



				//drawTextureBox(-40, 30, 80, 160, 0, 0, 256, 512, door2);


				// キャラの移動＆移動制限

				if (env.isPressKey(GLFW_KEY_UP)){
					y += 5;
					drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 1));
					if (y > 864.0f){
						y = 864.0f;

					}
				}

				else if (env.isPressKey(GLFW_KEY_LEFT)){
					x -= 5;
					drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
					
				}
				else if (env.isPressKey(GLFW_KEY_DOWN)){
					y -= 5;
					drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
					if(y< -1024.0f){
						y = -1024.0f;

					}
				}
				else if (env.isPressKey(GLFW_KEY_RIGHT)){
					x += 5;
					drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
					
				}
				else {
					drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
				}


				

				//マップ＆当たり判定
				//if(!( □+x<x ||　□x >x+80 ||　□+y <y ||　□y　> y+160))


				drawFillBox(500, -1024, 600, 2048, Color(0, 0, 0, 1));

				if (!(1100 < x || 500 > x + 80 || 1024 < y || -1024 > y + 100)){
					x = -40;
					y = -1024;
					
				}
				drawFillBox(-1100, -1024, 600, 2048, Color(0,0,0, 1));//0.02
				if (!(-500 < x || -1100 > x + 80 || 1024 < y || -1024 > y + 160)){
					x = -40;
					y = -1024;
				}
				drawFillBox(-300, 0, 500, 200, Color(0,0,0,1));
				if (!(200 < x || -300 > x + 80 || 200 < y || 0 > y + 160)){
					x = -40;
					y = -1024;
				}

				

			}






		//----------------------ステージ１--------------------------------------------------------------

			
				if (stage_count == 1){
					drawFillBox(-1024, -1024, 2048, 2048, Color(40 / 255, 34 / 255, 42 / 255, 1));

					drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
					if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
						if (env.isPressKey(GLFW_KEY_SPACE)){
							stage_count++;
							x = -40;
							y = -1024;
							nock.play();
						}

					}


					// キャラの移動＆移動制限

					if (env.isPressKey(GLFW_KEY_UP)){
						y += 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 0.4));
						if (y > 864.0f){
							y = 864.0f;

						}
					}

					else if (env.isPressKey(GLFW_KEY_LEFT)){
						x -= 5;
						drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 0.4));
						if (x < -1024.0f){
							x = -1024.0f;

						}
					}
					else if (env.isPressKey(GLFW_KEY_DOWN)){
						y -= 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 0.4));
						if (y < -1024.0f){
							y = -1024.0f;

						}
					}
					else if (env.isPressKey(GLFW_KEY_RIGHT)){
						x += 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 0.4));
						if (x > 1024.0f){
							x = 1024.0f;
						}
					}
					else {
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 0.4));
					}

					//マップ＆当たり判定
					//if(!( <x || >x+80 || <y ||> y+160))

					//if(!(ax2 < bx1 || ax1 > bx2 || ay1< by2 || ay2 >by1))

					drawFillBox(500, -1024, 100, 2048, Color(1, 1, 1, 0.02));

					if (!(600 < x || 500 > x + 80 || 1024 < y || -1024 > y + 100)){
						x = -40;
						y = -1024;

					}
					drawFillBox(-500, -1024, 100, 2048, Color(1, 1, 1, 0.02));//0.02
					if (!(-400 < x || -500 > x + 80 || 1024 < y || -1024 > y + 160)){
						x = -40;
						y = -1024;
					}
					drawFillBox(-400, 0, 500, 200, Color(1, 1, 1, 0.02));
					if (!(100 < x || -400 > x + 80 || 200 < y || 0 > y + 160)){
						x = -40;
						y = -1024;
					}

					drawFillBox(0, -500, 500, 200, Color(1, 1, 1, 0.02));
					if (!(500 < x || 0 > x + 80 || -300 < y || -500 > y + 160)){
						x = -40;
						y = -1024;
					}

					drawFillBox(-150, 500, 400, 200, Color(1, 1, 1, 0.02));
					if (!(250 < x || -150 > x + 80 || 700 < y || 500 > y + 160)){
						x = -40;
						y = -1024;
					}
					//キャラの明かり
					drawFillCircle(x + 40, y + 80, 130, 130, 100, Color(1, 1, 1, 0.13));

				}


				//--------------------2ステージ------------------------------------------------------------
				if (stage_count == 2){

					drawFillBox(-1024, -1024, 2048, 2048, Color(1, 1, 1, 1));

					drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
					if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
						if (env.isPressKey(GLFW_KEY_SPACE)){
							stage_count++;

							x = -40;
							y = -1024;
							nock.play();
						}

					}


					// キャラの移動＆移動制限

					if (env.isPressKey(GLFW_KEY_UP)){
						y += 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 1));
						if (y > 864.0f){
							y = 864.0f;

						}
					}

					else if (env.isPressKey(GLFW_KEY_LEFT)){
						x -= 5;
						drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
						if (x < -1024.0f){
							x = -1024.0f;

						}
					}
					else if (env.isPressKey(GLFW_KEY_DOWN)){
						y -= 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
						if (y < -1024.0f){
							y = -1024.0f;

						}
					}
					else if (env.isPressKey(GLFW_KEY_RIGHT)){
						x += 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
						if (x > 1024.0f){
							x = 1024.0f;
						}
					}
					else {
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
					}

					//明かり的な？
					drawFillCircle(x + 40, y + 80, 130, 130, 100, Color(0, 0, 0, 0.1));
					//マップ＆当たり判定
					//if(!( <x || >x+80 || <y ||> y+160))

					//if(!(ax2 < bx1 || ax1 > bx2 || ay1< by2 || ay2 >by1))





					drawFillBox(500, -1024, 100, 2048, Color(1, 1, 1));
					if (!(600 < x || 500 > x + 80 || 1024 < y || -1024 > y + 100)){
						x = -40;
						y = -1024;

					}
					drawFillBox(-500, -1024, 100, 2048, Color(1, 1, 1));//0.02
					if (!(-400 < x || -500 > x + 80 || 1024 < y || -1024 > y + 160)){
						x = -40;
						y = -1024;
					}
					drawFillBox(-400, 0, 500, 200, Color(1, 1, 1));
					if (!(100 < x || -400 > x + 80 || 200 < y || 0 > y + 160)){
						x = -40;
						y = -1024;
					}

					drawFillBox(0, -500, 500, 200, Color(1, 1, 1));
					if (!(500 < x || 0 > x + 80 || -300 < y || -500 > y + 160)){
						x = -40;
						y = -1024;
					}

					drawFillBox(-150, 500, 400, 200, Color(1, 1, 1));
					if (!(250 < x || -150 > x + 80 || 700 < y || 500 > y + 160)){
						x = -40;
						y = -1024;
					}



				}


				//---------------------ステージ3-------------------------------------------------------------------------
				if (stage_count == 3){

					drawFillBox(-1024, -1024, 2048, 2048, Color(1, 1, 1, 1));

					drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
					if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
						if (env.isPressKey(GLFW_KEY_SPACE)){
							x = -1500;
							y = -1024;
							stage_count = 0;
							stage_clear = 1;
							nock.play();
							break;


						}

					}

					if (env.isPressKey(GLFW_KEY_UP)){
						y += 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 1));
						if (y > 864.0f){
							y = 864.0f;

						}
					}

					else if (env.isPressKey(GLFW_KEY_LEFT)){
						x -= 5;
						drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
						if (x < -1024.0f){
							x = -40;
							y = -1024;

						}
					}
					else if (env.isPressKey(GLFW_KEY_DOWN)){
						y -= 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
						if (y < -1024.0f){
							y = -1024.0f;

						}
					}
					else if (env.isPressKey(GLFW_KEY_RIGHT)){
						x += 5;
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
						if (x > 944.0f){
							x = -40;
							y = -1024;
						}
					}
					else {
						drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
					}





					drawFillBox(block_x, block_y, 200, 200, Color::black);


					if (!(block_x + 200 < x || block_x > x + 80 || block_y + 200 < y || block_y > y + 160)){
						x = -40;
						y = -1024;

					}
					if (!(200 < x || 0 > x + 80 || 400 < y || 200 > y + 160)){
						block_x = 0;

					}

				}
			
				//--------------------------------------------すてーじ１--------------------------------------------
				
				if (stage_count == 11){
					if (life == 3){
						drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
						drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
						drawTextureBox(1376, -1024, 128, 128, 0, 0, 128, 128, hp);
					}
					else if (life == 2){
						drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
						drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
					}
					else if (life == 1){
						drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
					}
					else {
						stage_count = 0;
						life = 3;
						x = -1500;
						y = -1024;
						break;

					}
						drawFillBox(-1024, -1024, 2048, 2048, Color(1, 1, 1, 1));

						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
						if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
							drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
							if (env.isPressKey(GLFW_KEY_SPACE)){
								x = -40;
								y = -1024;
								stage_count++;

								nock.play();



							}

						}

						if (env.isPressKey(GLFW_KEY_UP)){
							y += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1,1,1, 1));
							if (y > 864.0f){
								y = 864.0f;

							}
						}

						else if (env.isPressKey(GLFW_KEY_LEFT)){
							x -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
							if (x < -1024.0f){
								x = -40;
								y = -1024;

							}
						}
						else if (env.isPressKey(GLFW_KEY_DOWN)){
							y -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
							if (y < -1024.0f){
								y = -1024.0f;

							}
						}
						else if (env.isPressKey(GLFW_KEY_RIGHT)){
							x += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
							if (x > 944.0f){
								x = -40;
								y = -1024;
							}
						}
						else {
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
						}


						drawFillCircle(x + 40, y + 80, 130, 130, 100, Color(0, 0, 0, 0.1));
						drawFillBox(100, -1024, 300, 500, Color::white);
						if (!(400 < x || 100 > x + 80 || -524 < y || -1024 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(-1024, -1024, 800, 400, Color::white);
						if (!(-224 < x || -1024 > x + 80 || -624 < y || -1024 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(-600, -224, 1000, 300, Color::white);
						if (!(400 < x || -600 > x + 80 || -124 < y || -224 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(400, 70, 600, 300, Color::white);
						if (!(1100 < x || 400 > x + 80 || 370 < y || 70 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(-600, 24, 300, 300, Color::white);
						if (!(-300 < x || -600 > x + 80 || 324 < y || 300 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(-600, 524, 300, 200, Color::white);
						if (!(-300 < x || -600 > x + 80 || 724 < y || 524 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(-300, 524, 300, 100, Color::white);
						if (!(0 < x || -300 > x + 80 || 624 < y || 524 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(0, 350, 400, 276, Color::white);
						if (!(400 < x || 0 > x + 80 || 626 < y || 350 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
					}

					//-------------------------------------すてーじ２----------------------------------------
					if (stage_count == 12){
						if (life == 3){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1376, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else if (life == 2){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else if (life == 1){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else {
							stage_count = 0;
							life = 3;
							x = -1500;
							y = -1024;
							akari_count = 0;
							break;

						}
						drawFillBox(-1024, -1024, 2048, 2048, Color(0, 0, 0, 1));
						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
						if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
							drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
							if (env.isPressKey(GLFW_KEY_SPACE)){
								x = -40;
								y = -1024;
								stage_count++;
								akari_count = 0;
								nock.play();



							}

						}

						if (env.isPressKey(GLFW_KEY_UP)){
							y += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 1));
							if (y > 864.0f){
								y = 864.0f;

							}
						}

						else if (env.isPressKey(GLFW_KEY_LEFT)){
							x -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
							if (x < -1024.0f){
								x = -40;
								y = -1024;

							}
						}
						else if (env.isPressKey(GLFW_KEY_DOWN)){
							y -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
							if (y < -1024.0f){
								y = -1024.0f;

							}
						}
						else if (env.isPressKey(GLFW_KEY_RIGHT)){
							x += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
							if (x > 944.0f){
								x = -40;
								y = -1024;
							}
						}
						else {
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));

						}


						drawFillBox(-1024, -1024, 800, 600, Color::black);
						if (!(-224<x ||-1024 >x + 80 ||-424 <y ||-1024 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(200, -1024, 500, 800, Color::black); 
							if (!(700<x ||200 >x + 80 ||-224 <y || -1024> y + 160)){
								x = -40;
								y = -1024;
								life--;
						}
						drawFillBox(-724, -250, 2000, 300, Color::black); 
							if (!(1276<x || -724 >x + 80 || 50<y || -250> y + 160)){
								x = -40;
								y = -1024;
								life--;
						}
						drawFillBox(-1024, 300, 1748, 200, Color::black); 
							if (!(724<x ||-1024 >x + 80 ||500 <y ||300 > y + 160)){
								x = -40;
								y = -1024;
								life--;
						}
						drawFillBox(60, 700, 1000, 424, Color::black); 
							if (!(1060<x ||60 >x + 80 || 1124<y ||700 > y + 160)){
								x = -40;
								y = -1024;
								life--;
						}


							
						akari_count++;
						if (akari_count < 90){
							drawTextureBox(-50, -350, 64, 64, 0, 0, 64, 64, akari);
						}
						if (akari_count > 90 && akari_count < 180){
							drawTextureBox(-900, -350, 64, 64, 0, 0, 64, 64, akari);
						}
						if (akari_count>180 && akari_count < 270){
							drawTextureBox(-900, 150, 64, 64, 0, 0, 64, 64, akari);
						}
						if (akari_count>270 && akari_count < 360){
							drawTextureBox(850, 150, 64, 64, 0, 0, 64, 64, akari);
						}
						if (akari_count>360 && akari_count < 450){
							drawTextureBox(850, 550, 64, 64, 0, 0, 64, 64, akari);
						}
						if (akari_count>450 && akari_count < 540){
							drawTextureBox(-40, 600, 64, 64, 0, 0, 64, 64, akari);
						}
						if (akari_count > 630){
							akari_count = 0;
						}



					}
					//------------------------------------------すてーじ３----------------------------
					if (stage_count == 13){
						if (life == 3){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1376, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else if (life == 2){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else if (life == 1){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else {
							stage_count = 0;
							life = 3;
							x = -40;
							y = -1024;
							akari_count = 0;
							break;

						}

						atari_count++;
						drawFillBox(-1024, -1024, 2048, 2048, Color(0, 0, 0, 1));
						if (atari_count == 600){
							if (!(1024 < x || -1024 > x + 80 || 1024 < y || -1024 > y + 160)){
								x = -40;
								y = -1024;
								life--;
							}
						}
						if(atari_count > 600){
							atari_count = 0;
						}

						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
						if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
							drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
							if (env.isPressKey(GLFW_KEY_SPACE)){
								x = -40;
								y = -1024;
								stage_count++;
								akari_count = 0;
								nock.play();



							}

						}

						if (env.isPressKey(GLFW_KEY_UP)){
							y += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 1));
							if (y > 864.0f){
								y = 864.0f;

							}
						}

						else if (env.isPressKey(GLFW_KEY_LEFT)){
							x -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
							if (x < -1024.0f){
								x = -40;
								y = -1024;

							}
						}
						else if (env.isPressKey(GLFW_KEY_DOWN)){
							y -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
							if (y < -1024.0f){
								y = -1024.0f;

							}
						}
						else if (env.isPressKey(GLFW_KEY_RIGHT)){
							x += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
							if (x > 944.0f){
								x = -40;
								y = -1024;
							}
						}
						else {
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));

						}


				//----------------------------------------すてーじ１４-------------------------------
					}
					if (stage_count == 14){
						if (life == 3){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1376, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else if (life == 2){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
							drawTextureBox(1218, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else if (life == 1){
							drawTextureBox(1050, -1024, 128, 128, 0, 0, 128, 128, hp);
						}
						else {
							stage_count = 0;
							life = 3;
							x = -1500;
							y = -1024;
							akari_count = 0;
							break;

						}
						drawFillBox(-1024, -1024, 2048, 2048, Color(1, 1, 1, 1));
						drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door);
						if (!(60 < x || -40 > x + 80 || 1024 < y || 824 > y + 160)){
							drawTextureBox(-40, 824, 100, 200, 0, 0, 256, 512, door2);
							if (env.isPressKey(GLFW_KEY_SPACE)){
								x = -40;
								y = -1024;
								stage_count++;
								akari_count = 0;
								nock.play();



							}

						}
						drawFillBox(-200, -300, 100, 100, Color::white);
						if (!(-100<x || -300 >x + 80 || -200 <y || -300 > y + 160)){
							x = 100;
							y = -700;
						}
						drawFillBox(100, 0, 100, 100, Color::white);
						if (!(200<x || 100>x + 80 || 100<y || 0> y + 160)){
							x = 300;
							y = -50;
						}
						drawFillBox(-500, -300, 100, 100, Color::white);
						if (!(-400<x || -500>x + 80 || -400 <y || -300 > y + 160)){
							x = 200;
							y = -100;
						}
						drawFillBox(-700, -400, 100, 100, Color::white);
						if (!(-600<x || -700>x + 80 || -300<y || -400> y + 160)){
							x = 700;
							y = -200;
						}
						drawFillBox(-500, -300, 100, 100, Color::white);
						if (!(-400<x || -500 >x + 80 || -400 <y || -300 > y + 160)){
							x = 400;
							y = 500;
						}
						drawFillBox(300, 0, 100, 100, Color::white);
						if (!(400<x || 300>x + 80 || 100 <y || 0 > y + 160)){
							x = -200;
							y = -900;
						}
						drawFillBox(-800, -300, 100, 100, Color::white);
						if (!(-700<x || -800 >x + 80 || -200 <y || -300> y + 160)){
							x = -600;
							y = 300;
						}
						drawFillBox(-300, -400, 100, 100, Color::white);
						if (!(-200<x || -300 >x + 80 || -300 <y || -400> y + 160)){
							x = -500;
							y = 800;
						}
						drawFillBox(300, 300, 100, 100, Color::white);
						if (!(400<x || 300>x + 80 || 400 <y || 300> y + 160)){
							x = 900;
							y = -300;
						}
						drawFillBox(0, 600, 100, 100, Color::white);
						if (!(100<x || 0>x + 80 || 700 <y || 600> y + 160)){
							x = 800;
							y = 700;
						}
						drawFillBox(700, 0, 100, 100, Color::white);
						if (!(800<x || 700 >x + 80 || 100 <y || 0> y + 160)){
							x = -700;
							y = 800;
						}
						drawFillBox(500, -200, 100, 100, Color::white);
						if (!(600<x || 500 >x + 80 || -100 <y || -200 > y + 160)){
							x = -400;
							y = 400;
						}
						drawFillBox(900, -400, 100, 100, Color::white);
						if (!(1000<x || 900 >x + 80 || 900<y || -400 > y + 160)){
							x = -1000;
							y = 800;
						}
						drawFillBox(400, -600, 100, 100, Color::white);
						if (!(500<x || 400 >x + 80 || -500 <y || -600> y + 160)){
							x = -200;
							y = -800;
						}
						drawFillBox(300, -800, 100, 100, Color::white);

						drawFillBox(500, -900, 100, 100, Color::white);
						if (!(600<x || 500 >x + 80 || -800 <y || -900> y + 160)){
							x = 300;
							y = -50;
						}

						if (env.isPressKey(GLFW_KEY_UP)){
							y += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_back, Color(1, 1, 1, 1));
							if (y > 864.0f){
								y = 864.0f;

							}
						}

						else if (env.isPressKey(GLFW_KEY_LEFT)){
							x -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, -256, 512, anb_side, Color(1, 1, 1, 1));
							if (x < -1024.0f){
								x = -40;
								y = -1024;

							}
						}
						else if (env.isPressKey(GLFW_KEY_DOWN)){
							y -= 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));
							if (y < -1024.0f){
								y = -1024.0f;

							}
						}
						else if (env.isPressKey(GLFW_KEY_RIGHT)){
							x += 5;
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_side, Color(1, 1, 1, 1));
							if (x > 944.0f){
								x = -40;
								y = -1024;
							}
						}
						else {
							drawTextureBox(x, y, 80, 160, 0, 0, 256, 512, anb_top, Color(1, 1, 1, 1));

						}
						
						

						drawFillBox(-400, 400, 200, 824, Color::black);
						if (!(-200<x ||-400 >x + 80 ||600 <y ||400 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(200, 400, 200, 824, Color::black);
						if (!(400<x || 200>x + 80 ||1224 <y ||400 > y + 160)){
							x = -40;
							y = -1024;
							life--;
						}
						drawFillBox(-100, 0, 200, 200, Color::black);
						if (!(100 < x || -100 > x + 80 || 200 < y || 0 > y + 160))
						{
							x = -40;
							y = -1024;
							life--;
						}





						


						


					}
				
			//-------------------------------エンド画面------------------------------------------
			if (stage_count == 15){
				drawTextureBox(-1500, -1024, 3000, 2048, 0, 0, 4096, 2048, end);
				if (env.isPushButton(Mouse::LEFT)){
					x = -1500;
					y = -1024;
					break;
				}

			}
			if (env.isPushKey(GLFW_KEY_CAPS_LOCK)){
				stage_count++;

			}
		
				env.end();
			
		}
		//ここまでが本編while


		
		
		if (!env.isOpen()){
			return 0;

		}
		
































































































































































































		env.end();
	}
//*********************************************ここまで**************************************
}
//comein











































































