// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "log.h"
#include "md3_node.h"

md3_node::md3_node()
{
  m_md3_model = new CModelMD3; // TODO get resource
  log(msg() << "Loading md3 model...");

  static resource_manager rm;  // TODO TEMP TEST

  m_md3_model->LoadModel("md3/dragon/", rm);
  log(msg() << "Loaded md3 model ok!");
}

void md3_node::render() const
{
  m_md3_model->DrawModel();

  // Just for a quick test - no good for real, as we would update every render pass!
  m_md3_model->Update(); // TODO TEMP TEST
}


