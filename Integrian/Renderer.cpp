#include "IntegrianPCH.h"
#include "Renderer.h"
#include "Camera.h"
#include "GameObject.h"

void Integrian::Renderer::SetClearColour(const RGBColour& colour) noexcept
{
	m_ClearColour = colour;
}

void Integrian::Renderer::Render(GameObject* pGameObject) noexcept
{
	m_pGameObjectsToRender.push_back(pGameObject);
}

void Integrian::Renderer::ClearBackground() noexcept
{
	glClearColor(m_ClearColour.r / 255.f, m_ClearColour.g / 255.f, m_ClearColour.b / 255.f, m_ClearColour.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Integrian::Renderer::StartRenderLoop(SDL_Window* pWindow) noexcept
{
	ClearBackground();
	// == YOU CAN CHANGE THE TYPE OF THE CAMERA ==
	// == DO NOT CHANGE THE IMPLENTATION OF THIS FUNCTION UNLESS YOU EXPLICITLY WANT TO CHANGE HOW THE CAMERA WORKS ==
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(pWindow);
	ImGui::NewFrame();

	glPushMatrix();
}

void Integrian::Renderer::EndRenderLoop(SDL_Window* pWindow) noexcept
{
	glPopMatrix();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// == Swap back- and frontbuffer ==
	SDL_GL_SwapWindow(pWindow);

	m_pGameObjectsToRender.clear();
}

void Integrian::Renderer::RenderAll(const std::unique_ptr<Camera>& pCamera, const Rectf& target) noexcept
{
	pCamera->Transform(target);

	for (GameObject* pGameObject : m_pGameObjectsToRender)
		pGameObject->Render();
}
