// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

class state
{
public:
  virtual ~state() = default;
  virtual void on_enter() {}
  virtual void on_exit() {}
  virtual void render_on_gl_thread() const = 0;
  virtual void update(float dt) = 0;

protected:
  bool m_is_stereo = false;
};

