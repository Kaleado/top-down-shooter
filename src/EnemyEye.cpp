#include "EnemyEye.hpp"

void EnemyEye::_whenAttacking(){
  static bool hasAttacked = false;
  setXVelocity(0);
  setYVelocity(0);
  if(!hasAttacked){
    _currentAnimation = Animation({"res/orb-attacking.png", "res/orb.png", "res/orb-attacking.png", "res/orb.png", "res/orb-attacking.png"}, false, 10);
    _isAnimating = true;
    auto attackVec = getUnitVectorBetween(getWorldCenter(), player->getWorldCenter());
    double bulletSpeed = 15.0;
    attackVec.x *= bulletSpeed;
    attackVec.y *= bulletSpeed;
    std::shared_ptr<Bullet> attack = std::make_shared<Bullet>(false, "res/laser-crest.png", getWorldCenter(), 40, attackVec);
    playfield->addThing(attack);
    hasAttacked = true;
  }
  else if(--_attackCooldown <= 0){
    hasAttacked = false;
    enemyState = ES_AGGRO;
    _attackCooldown = FRAMERATE*1.2;
  }
}

void EnemyEye::_whenAggro(){
  _facing = getUnitVectorBetween(_position, player->getWorldPosition());
  _setImageBasedOnFacing();
  double dist = _getDistanceFromPlayer();
  double attackRange = 500;
  if(dist <= attackRange){
    enemyState = ES_ATTACKING;
  }
}

void EnemyEye::_whenIdle(){
  double aggroThreshold = 350;
  if(_getDistanceFromPlayer() < aggroThreshold){
    enemyState = ES_AGGRO;
  }
}
