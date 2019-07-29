#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics3D.h"

#include <unordered_set>

class CarCrimeCity : public olc::PixelGameEngine
{
public:
	CarCrimeCity()
	{
		sAppName = "Car Crime City";
	}

public:
	bool OnUserCreate() override
	{
		// load full spritesheet
		sprAll = new olc::Sprite("res/City_Roads1_mip0.png");

		// load separate sprites from the spritesheet:
		// building roof
		sprFrontage = new olc::Sprite(32, 96);
		SetDrawTarget(sprFrontage);
		DrawPartialSprite(0, 0, sprAll, 288, 64, 32, 96);

		// windows
		sprWindows = new olc::Sprite(32, 96);
		SetDrawTarget(sprWindows);
		DrawPartialSprite(0, 0, sprAll, 320, 64, 32, 96);

		// road
		for (int r = 0; r < 12; r++) {
			sprRoad[r] = new olc::Sprite(96, 96);
			SetDrawTarget(sprRoad[r]);
			DrawPartialSprite(0, 0, sprAll, (r % 3) * 96, (r / 3) * 96, 96, 96);
		}

		// grass
		sprGround = new olc::Sprite(96, 96);
		SetDrawTarget(sprGround);
		DrawPartialSprite(0, 0, sprAll, 192, 0, 96, 96);

		// roof
		sprRoof = new olc::Sprite(96, 96);
		SetDrawTarget(sprRoof);
		DrawPartialSprite(0, 0, sprAll, 352, 64, 96, 96);

		// ! set draw target back to null !
		SetDrawTarget(nullptr);

		// the car
		sprCar = new olc::Sprite("res/car_top.png");

		// A cube
		meshCube.tris = {

			// SOUTH
			{ 0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,},
			{ 0.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,},

			// EAST           																			   
			{ 1.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,},
			{ 1.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,},

			// NORTH           																			   
			{ 1.0f, 0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,},
			{ 1.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,},

			// WEST            																			   
			{ 0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,},
			{ 0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,},

			// TOP             																			   
			{ 0.0f, 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,},
			{ 0.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,},

			// BOTTOM          																			  
			{ 1.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,},
			{ 1.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,},

		};

		// A Flat quad
		meshFlat.tris =
		{
			{ 0.0f, 0.0f, 0.0f, 1.0f,	    0.0f, 1.0f, 0.0f, 1.0f,		 1.0f, 1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, 		1.0f, 1.0f, 0.0f, },
			{ 0.0f, 0.0f, 0.0f, 1.0f,  		1.0f, 1.0f, 0.0f, 1.0f,		 1.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f, 		1.0f, 0.0f, 0.0f, },
		};

		// The four outer walls of a cell
		meshWallsOut.tris =
		{
			// EAST
			{ 1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.2f, 1.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 		0.0f, 0.0f, 0.0f, },
			{ 1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.2f, 1.0f,		1.0f, 0.0f, 0.2f, 1.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 		0.0f, 1.0f, 0.0f, },

			// WEST
			{ 0.0f, 0.0f, 0.2f, 1.0f,		0.0f, 1.0f, 0.2f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 		1.0f, 0.0f, 0.0f, },
			{ 0.0f, 0.0f, 0.2f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 		1.0f, 1.0f, 0.0f, },

			// TOP             																 				    
			{ 0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.2f, 1.0f,		1.0f, 1.0f, 0.2f, 1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,   },
			{ 0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.2f, 1.0f,		1.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, 		1.0f, 1.0f, 0.0f,   },

			// BOTTOM         																 				   
			{ 1.0f, 0.0f, 0.2f, 1.0f,		0.0f, 0.0f, 0.2f, 1.0f,		0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 		1.0f, 0.0f, 0.0f, },
			{ 1.0f, 0.0f, 0.2f, 1.0f,		0.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 		1.0f, 1.0f, 0.0f, },
		};

		olc::GFX3D::ConfigureDisplay();

		pipeRender.SetProjection(90.f, (float)ScreenHeight() / (float)ScreenWidth(), 0.1f, 1000.f, 0.f, 0.f, ScreenWidth(), ScreenHeight());

		matProj = olc::GFX3D::Math::Mat_MakeProjection(90.0f, (float)ScreenHeight() / (float)ScreenWidth(), 0.1f, 1000.0f);


		// city map
		nMapWidth = 64;
		nMapHeight = 32;
		pMap = new sCell[nMapWidth * nMapHeight];
		for (int x = 0; x < nMapWidth; x++)
		{
			for (int y = 0; y < nMapHeight; y++) 
			{
				pMap[y * nMapWidth + x].nHeight = 0;
				pMap[y * nMapWidth + x].bRoad = false;
				pMap[y * nMapWidth + x].nWorldX = x;
				pMap[y * nMapWidth + x].nWorldY = y;
			}
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::W).bHeld) fCameraY -= 2.0f * fElapsedTime;
		if (GetKey(olc::Key::S).bHeld) fCameraY += 2.0f * fElapsedTime;
		if (GetKey(olc::Key::A).bHeld) fCameraX -= 2.0f * fElapsedTime;
		if (GetKey(olc::Key::D).bHeld) fCameraX += 2.0f * fElapsedTime;
		if (GetKey(olc::Key::Z).bHeld) fCameraZ += 5.0f * fElapsedTime;
		if (GetKey(olc::Key::X).bHeld) fCameraZ -= 5.0f * fElapsedTime;

		if (GetKey(olc::Key::LEFT).bHeld) fCarAngle -= 4.0f * fElapsedTime;
		if (GetKey(olc::Key::RIGHT).bHeld) fCarAngle += 4.0f * fElapsedTime;

		olc::GFX3D::vec3d a = { 1, 0, 0 };
		olc::GFX3D::mat4x4 m = olc::GFX3D::Math::Mat_MakeRotationZ(fCarAngle);
		vecCarVel = olc::GFX3D::Math::Mat_MultiplyVector(m, a);

		if (GetKey(olc::Key::UP).bHeld)
		{
			vecCarPos.x += vecCarVel.x * fCarSpeed * fElapsedTime;
			vecCarPos.y += vecCarVel.y * fCarSpeed * fElapsedTime;
		}

		if (nMouseWorldX >= 0 && nMouseWorldX < nMapWidth && nMouseWorldY >= 0 && nMouseWorldY < nMapHeight) 
		{
			if (GetKey(olc::Key::R).bPressed)
			{
				if (!setSelectedCells.empty())
				{
					for (auto& cell : setSelectedCells)
					{
						cell->bRoad = !cell->bRoad;
					}
				}
				else 
					pMap[nMouseWorldY * nMapWidth + nMouseWorldX].bRoad = !pMap[nMouseWorldY * nMapWidth + nMouseWorldX].bRoad;
			}

			if (GetKey(olc::Key::T).bPressed)
			{
				if (!setSelectedCells.empty())
				{
					for (auto& cell : setSelectedCells)
					{
						cell->nHeight++;
					}
				}
				else
					pMap[nMouseWorldY * nMapWidth + nMouseWorldX].nHeight++;
			}

			if (GetKey(olc::Key::E).bPressed)
			{
				if (!setSelectedCells.empty())
				{
					for (auto& cell : setSelectedCells)
					{
						cell->nHeight--;
					}
				}
				else
					pMap[nMouseWorldY * nMapWidth + nMouseWorldX].nHeight--;
			}
		}

		Clear(olc::BLUE);
		olc::GFX3D::ClearDepth();

		olc::GFX3D::vec3d vLookTarget = olc::GFX3D::Math::Vec_Add(vEye, vLookDir);

		vEye = { vecCarPos.x, vecCarPos.y, fCameraZ };
		pipeRender.SetCamera(vEye, vLookTarget, vUp);

		// assume mouse origin is in the centre of the screen
		olc::GFX3D::vec3d vecMouseOrigin = { 0.f, 0.f, 0.f };
		// translate mouse coords to viewport coords
		olc::GFX3D::vec3d vecMouseDir = {
			2.f * ((GetMouseX() / (float)ScreenWidth()) - 0.5f) / matProj.m[0][0],
			2.f * ((GetMouseY() / (float)ScreenHeight()) - 0.5f) / matProj.m[1][1],
			1.f,
			0.f
		};

		olc::GFX3D::mat4x4 matView = olc::GFX3D::Math::Mat_PointAt(vEye, vLookTarget, vUp);

		vecMouseOrigin = olc::GFX3D::Math::Mat_MultiplyVector(matView, vecMouseOrigin);
		vecMouseDir = olc::GFX3D::Math::Mat_MultiplyVector(matView, vecMouseDir);

		vecMouseDir = olc::GFX3D::Math::Vec_Mul(vecMouseDir, 1000.f);	
		vecMouseDir = olc::GFX3D::Math::Vec_Add(vecMouseOrigin, vecMouseDir);

		olc::GFX3D::vec3d plane_p = { 0.f, 0.f, 0.f };
		olc::GFX3D::vec3d plane_n = { 0.f, 0.f, 1.f };

		float t = 0.f;
		olc::GFX3D::vec3d mouse3d = olc::GFX3D::Math::Vec_IntersectPlane(plane_p, plane_n, vecMouseOrigin, vecMouseDir, t);
		nMouseWorldX = (int)mouse3d.x;
		nMouseWorldY = (int)mouse3d.y;

		if (GetMouse(0).bHeld)
		{
			setSelectedCells.emplace(&pMap[nMouseWorldY * nMapWidth + nMouseWorldX]);
		}

		if (GetMouse(1).bReleased)
		{
			setSelectedCells.clear();
		}

		// top left ground cell
		vecMouseDir = { -1.0f / matProj.m[0][0],-1.0f / matProj.m[1][1], 1.0f, 0.0f };
		vecMouseDir = olc::GFX3D::Math::Mat_MultiplyVector(matView, vecMouseDir);
		vecMouseDir = olc::GFX3D::Math::Vec_Mul(vecMouseDir, 1000.0f);
		vecMouseDir = olc::GFX3D::Math::Vec_Add(vecMouseOrigin, vecMouseDir);
		viewWorldTopLeft = olc::GFX3D::Math::Vec_IntersectPlane(plane_p, plane_n, vecMouseOrigin, vecMouseDir, t);

		// bottom right ground cell
		vecMouseDir = { 1.0f / matProj.m[0][0], 1.0f / matProj.m[1][1], 1.0f, 0.0f };
		vecMouseDir = olc::GFX3D::Math::Mat_MultiplyVector(matView, vecMouseDir);
		vecMouseDir = olc::GFX3D::Math::Vec_Mul(vecMouseDir, 1000.0f);
		vecMouseDir = olc::GFX3D::Math::Vec_Add(vecMouseOrigin, vecMouseDir);
		viewWorldBottomRight = olc::GFX3D::Math::Vec_IntersectPlane(plane_p, plane_n, vecMouseOrigin, vecMouseDir, t);

		int nStartX = std::max(0, (int)viewWorldTopLeft.x - 1);
		int nEndX = std::min(nMapWidth, (int)viewWorldBottomRight.x + 1);
		int nStartY = std::max(0, (int)viewWorldTopLeft.y - 1);
		int nEndY = std::min(nMapHeight, (int)viewWorldBottomRight.y + 1);

		for (int x = nStartX; x < nEndX; x++)
		{
			for (int y = nStartY; y < nEndY; y++) 
			{				
				if (pMap[y * nMapWidth + x].bRoad)
				{
					int road = 0;

					auto r = [&](int i, int j)
					{
						return pMap[(y + j) * nMapWidth + (x + i)].bRoad;
					};

					if (r(0, -1) && r(0, +1) && !r(-1, 0) && !r(+1, 0)) road = 0;
					if (!r(0, -1) && !r(0, +1) && r(-1, 0) && r(+1, 0)) road = 1;

					if (!r(0, -1) && r(0, +1) && !r(-1, 0) && r(+1, 0)) road = 3;
					if (!r(0, -1) && r(0, +1) && r(-1, 0) && r(+1, 0)) road = 4;
					if (!r(0, -1) && r(0, +1) && r(-1, 0) && !r(+1, 0)) road = 5;

					if (r(0, -1) && r(0, +1) && !r(-1, 0) && r(+1, 0)) road = 6;
					if (r(0, -1) && r(0, +1) && r(-1, 0) && r(+1, 0)) road = 7;
					if (r(0, -1) && r(0, +1) && r(-1, 0) && !r(+1, 0)) road = 8;

					if (r(0, -1) && !r(0, +1) && !r(-1, 0) && r(+1, 0)) road = 9;
					if (r(0, -1) && !r(0, +1) && r(-1, 0) && r(+1, 0)) road = 10;
					if (r(0, -1) && !r(0, +1) && r(-1, 0) && !r(+1, 0)) road = 11;

					pipeRender.SetTexture(sprRoad[road]);
					olc::GFX3D::mat4x4 matWorld = olc::GFX3D::Math::Mat_MakeTranslation(x, y, 0.f);
					pipeRender.SetTransform(matWorld);
					pipeRender.Render(meshFlat.tris);
				}
				else
				{
					if (pMap[y * nMapWidth + x].nHeight < 0) {}

					if (pMap[y * nMapWidth + x].nHeight == 0)
					{
						// ground 
						olc::GFX3D::mat4x4 matWorld = olc::GFX3D::Math::Mat_MakeTranslation(x, y, 0.f);
						pipeRender.SetTransform(matWorld);
						pipeRender.SetTexture(sprGround);
						pipeRender.Render(meshFlat.tris);
					}

					if (pMap[y * nMapWidth + x].nHeight > 0) 
					{
						int h;
						for (h = 0; h < pMap[y * nMapWidth + x].nHeight; h++)
						{
							olc::GFX3D::mat4x4 matWorld = olc::GFX3D::Math::Mat_MakeTranslation(x, y, -(h + 1) * 0.2f);
							pipeRender.SetTransform(matWorld);

							pipeRender.SetTexture(h == 0 ? sprFrontage : sprWindows);
							pipeRender.Render(meshWallsOut.tris);
						} 

						olc::GFX3D::mat4x4 matWorld = olc::GFX3D::Math::Mat_MakeTranslation(x, y, -(h) * 0.2f);
						pipeRender.SetTransform(matWorld);
						pipeRender.SetTexture(sprRoof);
						pipeRender.Render(meshFlat.tris);
					}
				}
			}
		}		

		// draw selected cells
		for (auto& cell : setSelectedCells)
		{
			olc::GFX3D::mat4x4 matWorld = olc::GFX3D::Math::Mat_MakeTranslation(cell->nWorldX, cell->nWorldY, 0.f);
			pipeRender.SetTransform(matWorld);
			pipeRender.Render(meshFlat.tris, olc::GFX3D::RENDER_WIRE);
		}

		// draw car
		// set origin to the centre of the quad
		olc::GFX3D::mat4x4 matCarOffset = olc::GFX3D::Math::Mat_MakeTranslation(-0.5f, -0.5f, -0.0f);
		olc::GFX3D::mat4x4 matCarScale = olc::GFX3D::Math::Mat_MakeScale(0.4f, 0.2f, 1.0f);
		olc::GFX3D::mat4x4 matCar = olc::GFX3D::Math::Mat_MultiplyMatrix(matCarOffset, matCarScale);
		olc::GFX3D::mat4x4 matCarRot = olc::GFX3D::Math::Mat_MakeRotationZ(fCarAngle);
		matCar = olc::GFX3D::Math::Mat_MultiplyMatrix(matCar, matCarRot);
		olc::GFX3D::mat4x4 matCarTrans = olc::GFX3D::Math::Mat_MakeTranslation(vecCarPos.x, vecCarPos.y, -0.01f);
		matCar = olc::GFX3D::Math::Mat_MultiplyMatrix(matCar, matCarTrans);

		pipeRender.SetTransform(matCar);
		pipeRender.SetTexture(sprCar);

		SetPixelMode(olc::Pixel::ALPHA);
		pipeRender.Render(meshFlat.tris);
		SetPixelMode(olc::Pixel::NORMAL);

		return true;
	}

private:
	olc::GFX3D::mesh meshCube;
	olc::GFX3D::mesh meshFlat;
	olc::GFX3D::mesh meshWallsOut;

	olc::GFX3D::vec3d vUp{ 0, 1, 0 };
	olc::GFX3D::vec3d vEye{ 0, 0, -4 };
	olc::GFX3D::vec3d vLookDir{ 0, 0, 1 };

	olc::GFX3D::PipeLine pipeRender;

	olc::Sprite* sprAll;
	olc::Sprite* sprGround;
	olc::Sprite* sprRoof;
	olc::Sprite* sprFrontage;
	olc::Sprite* sprWindows;
	olc::Sprite* sprRoad[12];
	olc::Sprite* sprCar;

	float fTheta = 0.f;

	// cell
	struct sCell {
		int nHeight = 0;
		bool bRoad = false;
		int nWorldX, nWorldY;
	};

	// map variables
	int nMapWidth, nMapHeight;
	sCell* pMap;

	// camera position
	float fCameraX = 0.0f;
	float fCameraY = 0.0f;
	float fCameraZ = -10.0f;

	// car
	float fCarAngle = 0.f;
	float fCarSpeed = 2.0f;
	olc::GFX3D::vec3d vecCarVel{ 0, 0, 0 };
	olc::GFX3D::vec3d vecCarPos{ 0, 0, 0 };

	int nMouseWorldX = 0, nMouseWorldY = 0;
	olc::GFX3D::mat4x4 matProj;

	std::unordered_set<sCell*> setSelectedCells;

	olc::GFX3D::vec3d viewWorldTopLeft, viewWorldBottomRight;
};


int main()
{
	CarCrimeCity demo;
	if (demo.Construct(768, 480, 2, 2))
		demo.Start();

	return 0;
}
