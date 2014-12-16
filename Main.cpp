/*
 * Copyright (c) 2011-2014, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Karen Liu <karenliu@cc.gatech.edu>,
 *            Jeongseok Lee <jslee02@gmail.com>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */
#include "dart/math/helpers.h"
#include <iostream>
#include <vector>

#include "dart/utils/Paths.h"
#include "dart/dynamics/BodyNode.h"
#include "dart/dynamics/Joint.h"
#include "dart/dynamics/Skeleton.h"
#include "dart/simulation/World.h"
#include "dart/utils/SkelParser.h"
#include "dart/constraint/ConstraintSolver.h"
#include "dart/collision/dart/DARTCollisionDetector.h"
#include "MyWindow.h"

int main(int argc, char* argv[]) {
  // Create and initialize the world
  dart::simulation::World* myWorld
      = dart::utils::SkelParser::readWorld(
          DART_DATA_PATH"skel/monkeybars2.skel");
  assert(myWorld != NULL);

  Eigen::Vector3d gravity(0.0, -9.81, 0.0);
  myWorld->setGravity(gravity);

  dart::constraint::ConstraintSolver* cs = myWorld->getConstraintSolver();
  cs->setCollisionDetector(new dart::collision::DARTCollisionDetector());

  // Set initial pose
  std::vector<size_t> genCoordIds;
  genCoordIds.push_back(6);   // left hip
  genCoordIds.push_back(14);   // left knee
  genCoordIds.push_back(17);  // left ankle
  genCoordIds.push_back(9);  // right hip
  genCoordIds.push_back(15);  // right knee
  genCoordIds.push_back(19);  // right ankle
  Eigen::VectorXd initConfig(6);
  initConfig << 0.15, -0.4, 0.25, 0.15, -0.4, 0.25;
  myWorld->getSkeleton("fullbody1")->setPositionSegment(genCoordIds, initConfig);
  myWorld->getSkeleton("fullbody1")->computeForwardKinematics(true, true, false);

  // Randomize the location of the bars
  dart::math::seedRand();
  Eigen::VectorXd position;

  if(myWorld->getSkeleton("bar1")){
      position = myWorld->getSkeleton("bar1")->getPositions();
      position[3] += dart::math::random(-0.1, 0.1);
      position[4] += dart::math::random(-0.1, 0.1);

      myWorld->getSkeleton("bar1")->setPositions(position);
      myWorld->getSkeleton("bar1")->computeForwardKinematics(true, false, false);
      std::cout << "Bar1 position" << std::endl;
      std::cout << position.transpose() << std::endl;
  }

  if(myWorld->getSkeleton("bar2")){
      position = myWorld->getSkeleton("bar2")->getPositions();
      position[3] += dart::math::random(-0.1, 0.1);
      position[4] += dart::math::random(-0.1, 0.1);

      myWorld->getSkeleton("bar2")->setPositions(position);
      myWorld->getSkeleton("bar2")->computeForwardKinematics(true, false, false);
      std::cout << "Bar2 position" << std::endl;
      std::cout << position.transpose() << std::endl;
  }


  if(myWorld->getSkeleton("bar3")){
      position = myWorld->getSkeleton("bar3")->getPositions();
      position[3] += dart::math::random(-0.1, 0.1);
      position[4] += dart::math::random(-0.1, 0.1);

      myWorld->getSkeleton("bar3")->setPositions(position);
      myWorld->getSkeleton("bar3")->computeForwardKinematics(true, false, false);
      std::cout << "Bar3 position" << std::endl;
      std::cout << position.transpose() << std::endl;
  }

  if(myWorld->getSkeleton("bar4")){
      position = myWorld->getSkeleton("bar4")->getPositions();
      position[3] += dart::math::random(-0.1, 0.1);
      position[4] += dart::math::random(-0.1, 0.1);

      myWorld->getSkeleton("bar4")->setPositions(position);
      myWorld->getSkeleton("bar4")->computeForwardKinematics(true, false, false);
      std::cout << "Bar4 position" << std::endl;
      std::cout << position.transpose() << std::endl;
  }


  std::cout << "space bar: simulation on/off" << std::endl;
  std::cout << "'p': playback/stop" << std::endl;
  std::cout << "'[' and ']': play one frame backward and forward" << std::endl;
  std::cout << "'v': visualization on/off" << std::endl;
  // Create controller
  Controller* myController = new Controller(myWorld->getSkeleton("fullbody1"), myWorld->getConstraintSolver(),
                                            myWorld->getTimeStep(), myWorld);

  // Create a window and link it to the world
  MyWindow window;
  window.setWorld(myWorld);
  window.setController(myController);


  glutInit(&argc, argv);
  window.initWindow(640, 480, "Monkeybars");
  glutMainLoop();

  return 0;
}
