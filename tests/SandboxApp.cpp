#include "papayapch.h"

#include <Papaya/Papaya.h>

namespace Papaya {

class SandboxLayer : public Papaya::Layer
{
public:
  SandboxLayer()
    : Layer("SandboxLayer")
  {
  }

  ~SandboxLayer()
  {
  }

  virtual void OnAttach() override
  {
  }

  virtual void OnDetach() override
  {
  }

  virtual void OnUpdate(Papaya::Timestep ts) override
  {
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event>& event) override
  {
  }

private:
};

Game* CreateGame()
{
  Game* game = new Game();
  game->PushLayer(new SandboxLayer());
  return game;
}

} // namespace Papaya