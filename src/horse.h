#pragma once

#include <memory>
#include <vector>
#include <tuple>
#include <iostream>
#include <list>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helper.h"
#include "api/shader.h"

enum HorseStatus{
    status_run,
    status_walk,
    status_jump,
    status_stationary,
    status_rotate,
    none
};

enum HorsePart
{
    Torso = 0,
    Head = 1,
    LeftUpperArm = 2,
    LeftLowerArm = 3,
    RightUpperArm = 4,
    RightLowerArm = 5,
    LeftUpperLeg = 6,
    LeftLowerLeg = 7,
    RightUpperLeg = 8,
    RightLowerLeg = 9,
    Neck = 10
};

struct HorseDimension
{
    const double kTorsoHeight = 1.0;
    const double kTorsoWidth = 3.0;
    const double kTorsoDepth = 1.0;

    const double kNeckHeight = 1.5;
    const double kNeckWidth = 0.6;
    const double kNeckDepth = 0.6;

    const double kHeadHeight = 1.0;
    const double kHeadWidth = 0.5;
    const double kHeadDepth = 0.5;

    const double kUpperArmHeight = 1.0;
    const double kLowerArmHeight = 1.0;
    const double kUpperArmWidth  = 0.3;
    const double kLowerArmWidth  = 0.3;

    const double kUpperLegHeight = 1.0;
    const double kLowerLegHeight = 1.0;
    const double kUpperLegWidth  = 0.3;
    const double kLowerLegWidth = 0.3;
};

class Horse
{
public:
    static std::tuple<int, int> ground_[50][50];
    static unsigned global_id_;
    static float offset;
    unsigned texture_index_;
    unsigned id_;
    glm::vec4 color;
    glm::vec2 position_ = glm::vec2(-0.5f, 0.0f);
    float unit_ = 0.5f;
    glm::vec2 points[12];

    float offset_ = 10.0f;

    glm::vec2 vector_ = glm::vec2(-2.5, 0);

    HorseStatus status_ = HorseStatus::status_stationary;

    int tmp_step = 1;
    // to waste some frames to keep the horse run slowly
    int tmp_time = 0;
    int speedDivision = 10;

    float base_scale = 1.0f;

    float base_x = 0.0;
    float base_y = 0.0;
    float base_z = 0.0;

    float rotateX = 0.0;
    float rotateY = 0.0;
    float rotateZ = 0.0;

    unsigned collision_horse_id_ = 0;

    GLfloat theta[11] =
    {
        0.0,	// Torso
        80.0,	// Head
        190.0,	// LeftUpperArm
        -10.0,	// LeftLowerArm
        190.0,	// RightUpperArm
        -10.0,	// RightLowerArm
        180.0,	// LeftUpperLeg
        0.0,	// LeftLowerLeg
        180.0,	// RightUpperLeg
        0.0,	// RightLowerLeg
        45.0	// Neck
    };

    Horse();
    ~Horse();

    void Draw(Shader& shader);

    void run()
    {
        switch(tmp_step)
        {
        case 1 :
            theta[RightUpperLeg] = 150;
            theta[RightLowerLeg] = 90;
            theta[LeftUpperLeg] = 110;
            theta[LeftLowerLeg] = 90;
            theta[RightUpperArm] = 130;
            theta[RightLowerArm] = -10;
            theta[LeftUpperArm] = 150;
            theta[LeftLowerArm] = -20;
            theta[Neck] = 55;
            theta[Torso] = 0;
            break;
        case 2 :
            theta[RightUpperLeg] = 110;
            theta[RightLowerLeg] = 90;
            theta[LeftUpperLeg] = 110;
            theta[LeftLowerLeg] = 50;
            theta[RightUpperArm] = 170;
            theta[RightLowerArm] = -10;
            theta[LeftUpperArm] = 220;
            theta[LeftLowerArm] = -20;
            theta[Neck] = 45;
            theta[Torso] = -5;
            break;
        case 3 :
            theta[RightUpperLeg] = 120;
            theta[RightLowerLeg] = 70;
            theta[LeftUpperLeg] = 160;
            theta[LeftLowerLeg] = 0;
            theta[RightUpperArm] = 200;
            theta[RightLowerArm] = -30;
            theta[LeftUpperArm] = 250;
            theta[LeftLowerArm] = -10;
            theta[Neck] = 55;
            theta[Torso] = -2;
            break;
        case 4 :
            theta[RightUpperLeg] = 160;
            theta[RightLowerLeg] = 0;
            theta[LeftUpperLeg] = 190;
            theta[LeftLowerLeg] = 0;
            theta[RightUpperArm] = 220;
            theta[RightLowerArm] = -20;
            theta[LeftUpperArm] = 250;
            theta[LeftLowerArm] = -70;
            theta[Neck] = 45;
            theta[Torso] = 2;
            break;
        case 5 :
            theta[RightUpperLeg] = 190;
            theta[RightLowerLeg] = 0;
            theta[LeftUpperLeg] = 200;
            theta[LeftLowerLeg] = 10;
            theta[RightUpperArm] = 250;
            theta[RightLowerArm] = -90;
            theta[LeftUpperArm] = 230;
            theta[LeftLowerArm] = -90;
            theta[Neck] = 55;
            theta[Torso] = 5;
            break;
        case 6 :
            theta[RightUpperLeg] = 200;
            theta[RightLowerLeg] = 20;
            theta[LeftUpperLeg] = 170;
            theta[LeftLowerLeg] = 80;
            theta[RightUpperArm] = 210;
            theta[RightLowerArm] = -90;
            theta[LeftUpperArm] = 190;
            theta[LeftLowerArm] = -80;
            theta[Neck] = 55;
            theta[Torso] = 2;
            break;
        }
    }

    bool CollisionDetection(std::vector<Horse*> horse_list)
    {
        //std::cout << "(" << this->vector_.x << "," << this->vector_.y << ")"<<std::endl;
        //std::cout << "(" << this->position_.x << "," << this->position_.y << ")"<<std::endl;

        for(auto& h : horse_list)
        {
            if(h->id_ == this->id_)
            {
                continue;
            }
            glm::vec2 position0 = this->position_;
            glm::vec2 position1 = h->position_;
            float distance1 = glm::distance(position0, position1);
            if(distance1 == 0)
            {
                collision_horse_id_ = h->id_;
                return true;
            }
            glm::vec2 projection = position1 - position0;
            //std::cout << "pro:" << projection.x << " " << projection.y << std::endl;

            float dotProduct0 = glm::abs(glm::dot(this->vector_, projection));
            float scalarProjection0 = dotProduct0/glm::length(projection);
            //std::cout << "pro0:" << scalarProjection0 << std::endl;

            float dotProduct1 = glm::abs(glm::dot(h->vector_, projection));
            float scalarProjection1 = dotProduct1/glm::length(projection);
            //std::cout << "pro1:" << scalarProjection1 << std::endl;
            float distance0 = scalarProjection0 + scalarProjection1 + this->offset_ + h->offset_;
            //std::cout << "offset_: " << this->offset_ << " " << h->offset_<< ", dis1:"<< distance0 << ", dis2:" << glm::distance(position0, position1) <<std::endl;
            //std::cout << "pos: " << position0.x << "," << position0.y <<std::endl;
            //std::cout << "----------------->(" << position0.y << "),\t"<< "(" << position1.y << ")"<<std::endl;
            //std::cout << "(" << position0.x << "," << position0.y << "),\t"<< "(" << position1.x << "," << position1.y << ")"<<std::endl;
            //std::cout << "(" << this->vector_.x << "," << this->vector_.y << "),\t"<< "(" << h->vector_.x << "," << h->vector_.y << ")"<<std::endl;
            //std::cout << "offset_: " << this->offset_ << "," << h->offset_<<std::endl;
            //std::cout << "distance: "<< distance0 << "," << glm::distance(position0, position1) <<std::endl;
            //std::cout << "dist: " << distance0 << std::endl;

            if(distance0 > distance1)
            {
                collision_horse_id_ = h->id_;
                return true;
            }
        }
        return false;
    }

    bool ReachBoundary()
    {
        return glm::abs(glm::abs(this->position_.x) - 25) < 2.5 * base_scale || glm::abs(glm::abs(this->position_.y) - 25) < 2.5 * base_scale;
    }

    // Move straight ahead for (random) steps, rotate horse right or left (randomly) by 15 degrees.
    float walkStartFrame = 0.0f;
    float walkEndFrame = getRandomFromRange(100, 300);
    void BaseMove(std::vector<Horse*> horseList, float stepLength)
    {
        float originalBaseX = base_x;
        float originalBaseZ = base_z;
        if(status_ == HorseStatus::status_stationary){
            return;
        }else if(status_ == HorseStatus::status_walk){// walk
            ++walkStartFrame;
            base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
            base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
            this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
            if(walkStartFrame >= walkEndFrame){
                status_ = HorseStatus::status_rotate;// it's time to make a rotation
            }
        }else if(status_ == HorseStatus::status_rotate){// roate
            rotateY += getRandomBool() ? 15.0f : -15.0f;
            base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
            base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
            this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
            this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
            status_ = HorseStatus::status_walk;// set back to walk, so the horse continue to walk for a random time.
            walkStartFrame = 0;
            walkEndFrame = getRandomFromRange(100, 300);
        }

        while(this->CollisionDetection(horseList) || ReachBoundary())
        {
        // If the horse collides with another horse,
        // then randomly decide to hold one horse stationary and only move the other horse.
            if(ReachBoundary()){
                std::cout << "ReachBoundary;" << std::endl;
                rotateY = getRandomFromRange(0, 360);
                base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
                base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
                this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
                this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
            }else{
                if(getRandomBool()){// stop, wait the other horse to walk.
                    this->status_ = HorseStatus::status_stationary;
                    this->ResetTheta();
                    HorseStatus tmpHorseStatus;
                    for(auto& h : horseList)
                    {
                        if(h->id_ == this->collision_horse_id_){// find the status of the horse with smaller id
                            h->status_ = HorseStatus::status_walk;
                            break;
                        }
                    }
                    break;
                }else{
                    for(auto& h : horseList)
                    {
                        if(h->id_ == this->collision_horse_id_){// find the status of the horse with smaller id
                            h->status_ = HorseStatus::status_stationary;
                            h->ResetTheta();
                            break;
                        }
                    }
                    this->status_ = HorseStatus::status_walk;
                    rotateY = getRandomFromRange(0, 360);
                    base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
                    base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
                    this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
                    this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
                }

                /*
                if(this->id_ <= this->collision_horse_id_){// the one with smaller id should make a decision
                    if(getRandomBool()){// stop, wait the other horse to walk.
                        std::cout << "CollisionDetection:" << this->id_ << ": -------------------->stop" << std::endl;
                        this->status_ = HorseStatus::status_stationary;
                        break;
                    }else{// I would continue move, the other should stop
                        rotateY = getRandomFromRange(0, 360);
                        base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
                        base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
                        this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
                        this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
                    }
                }else{// the other one should have made a decision
                    HorseStatus tmpHorseStatus;
                    for(auto& h : horseList)
                    {
                        if(h->id_ == this->collision_horse_id_){// find the status of the horse with smaller id
                            tmpHorseStatus = h->status_;
                            break;
                        }
                    }
                    std::cout << "CollisionDetection:" << this->id_ << ":" << this->collision_horse_id_ << std::endl;
                    if(tmpHorseStatus == HorseStatus::status_stationary){// I should walk
                        this->status_ = HorseStatus::status_walk;
                        rotateY = getRandomFromRange(0, 360);
                        base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
                        base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
                        this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
                        this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
                    }else{
                        std::cout << "CollisionDetection:" << this->id_ << ": stop" << std::endl;
                        this->status_ = HorseStatus::status_stationary;
                        break;
                    }
                }*/
            }
        }
    }

    float ex_walkStartFrame = 0.0f;
    float ex_walkEndFrame = getRandomFromRange(100, 300);
    void ExtraMove(std::vector<Horse*> horseList, float stepLength)
    {
        float originalBaseX = base_x;
        float originalBaseZ = base_z;
        if(status_ == HorseStatus::status_stationary){
            return;
        }else if(status_ == HorseStatus::status_walk){// walk
            ++walkStartFrame;
            base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
            base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
            this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
            if(walkStartFrame >= walkEndFrame){
                status_ = HorseStatus::status_rotate;// it's time to make a rotation
            }
        }else if(status_ == HorseStatus::status_rotate){// roate
            rotateY += getRandomBool() ? 15.0f : -15.0f;
            base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
            base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
            this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
            this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
            status_ = HorseStatus::status_walk;// set back to walk, so the horse continue to walk for a random time.
            walkStartFrame = 0;
            walkEndFrame = getRandomFromRange(100, 300);
        }

        while(this->CollisionDetection(horseList) || ReachBoundary())
        {
        // If the horse collides with another horse,
        // then randomly decide to hold one horse stationary and only move the other horse.
            if(ReachBoundary()){
                std::cout << "ReachBoundary;" << std::endl;
                rotateY = getRandomFromRange(0, 360);
                base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
                base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
                this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
                this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
            }else{
                if(getRandomBool()){// stop, wait the other horse to walk.
                    this->status_ = HorseStatus::status_stationary;
                    this->ResetTheta();
                    HorseStatus tmpHorseStatus;
                    for(auto& h : horseList)
                    {
                        if(h->id_ == this->collision_horse_id_){// find the status of the horse with smaller id
                            h->status_ = HorseStatus::status_walk;
                            break;
                        }
                    }
                    break;
                }else{
                    for(auto& h : horseList)
                    {
                        if(h->id_ == this->collision_horse_id_){// find the status of the horse with smaller id
                            h->status_ = HorseStatus::status_stationary;
                            h->ResetTheta();
                            break;
                        }
                    }
                    this->status_ = HorseStatus::status_walk;
                    rotateY = getRandomFromRange(0, 360);
                    base_x = originalBaseX - stepLength * glm::cos(glm::radians(this->rotateY));
                    base_z = originalBaseZ + stepLength * glm::sin(glm::radians(this->rotateY));
                    this->position_ = glm::vec2(base_x * base_scale - 0.5, base_z * base_scale);
                    this->vector_ = glm::vec2(-2.5 * base_scale * glm::cos(glm::radians(rotateY)), 2.5 * base_scale * glm::sin(glm::radians(rotateY)));
                }
            }
        }
    }

    void BaseAnimation(std::vector<Horse*> horseList);

    void ExtraAnimation(std::vector<Horse*> horseList);

    void GenerateRandomHorse();

    void ResetModel()
    {
        base_scale = 1.0f;

        base_x = 0.0;
        base_y = 0.0;
        base_z = 0.0;

        rotateX = 0.0;
        rotateY = 0.0;
        rotateZ = 0.0;

        tmp_step = 1;
        tmp_time = 0;
        speedDivision = 10;
        status_ = HorseStatus::status_stationary;

        theta[Torso] = 0.0f;
        theta[Head] = 80.0f;
        theta[LeftUpperArm] = 190.0f;
        theta[LeftLowerArm] = -10.0f;
        theta[RightUpperArm] = 190.0f;
        theta[RightLowerArm] = -10.0f;
        theta[LeftUpperLeg] = 180.0f;
        theta[LeftLowerLeg] = 0.0f;
        theta[RightUpperLeg] = 180.0f;
        theta[RightLowerLeg] = 0.0f;
        theta[Neck] = 45.0f;
    }

    void ResetTheta()
    {
        theta[Torso] = 0.0f;
        theta[Head] = 80.0f;
        theta[LeftUpperArm] = 190.0f;
        theta[LeftLowerArm] = -10.0f;
        theta[RightUpperArm] = 190.0f;
        theta[RightLowerArm] = -10.0f;
        theta[LeftUpperLeg] = 180.0f;
        theta[LeftLowerLeg] = 0.0f;
        theta[RightUpperLeg] = 180.0f;
        theta[RightLowerLeg] = 0.0f;
        theta[Neck] = 45.0f;
    }

private:
    GLuint quadVAO_;
    Shader shader_;

    HorseDimension horse_dimension_;

    bool CheckCollisionByTwoDimensionArray()
    {
//      P9     P8     P7     P4     P5     P6
//      ------------------------------------
//      |      |      |      |      |      |
//      ------------------------------------
//      |      |      |  P0  |      |      |
//      ------------------------------------
//      P12    P11    P10    P1     P2     P3

        // step1: calculate these 12 points
        glm::vec2 vector1 = glm::vec2(glm::cos(glm::radians(rotateY)), -glm::sin(glm::radians(rotateY))) * unit_;
        glm::vec2 vector2 = glm::vec2(glm::sin(glm::radians(rotateY)), glm::cos(glm::radians(rotateY))) * unit_;
        points[0] = position_ + vector1 + vector2;
        points[1] = points[0] + vector1 + vector1;
        points[2] = points[1] + vector1 + vector1;
        points[3] = position_ + vector1 - vector2;
        points[4] = points[3] + vector1 + vector1;
        points[5] = points[4] + vector1 + vector1;
        points[6] = position_ - vector1 - vector2;
        points[7] = points[6] - vector1 - vector1;
        points[8] = points[7] - vector1 - vector1;
        points[9] = position_ - vector1 + vector2;
        points[10] = points[9] - vector1 - vector1;
        points[11] = points[10] - vector1 - vector1;

        /*
        points[0] = position_ + vector1;
        points[1] = points[0] + vector1;
        points[2] = points[1] + vector1;
        points[3] = points[2] + vector1;
        points[4] = points[3] + vector1;
        points[5] = points[4] + vector1;

        points[6] = position_ - vector1;
        points[7] = points[6] - vector1;
        points[8] = points[7] - vector1;
        points[9] = points[8] - vector1;
        points[10] = points[9] - vector1;

        points[11] = position_ + vector2;
        points[12] = points[11] + vector1;
        points[13] = points[12] + vector1;
        points[14] = points[13] + vector1;
        points[15] = points[14] + vector1;
        points[16] = points[15] + vector1;

        points[17] = position_ - vector2;
        points[18] = points[17] + vector1;
        points[19] = points[18] + vector1;
        points[20] = points[19] + vector1;
        points[21] = points[20] + vector1;
        points[22] = points[21] + vector1;

        points[23] = points[11] - vector1;
        points[24] = points[23] - vector1;
        points[25] = points[24] - vector1;
        points[26] = points[25] - vector1;
        points[27] = points[26] - vector1;

        points[28] = points[17] - vector1;
        points[29] = points[28] - vector1;
        points[30] = points[29] - vector1;
        points[31] = points[30] - vector1;
        */

        // step2: check whether the corresponding axis has been occupied.
        for(glm::vec2 vec2 : points)
        {
            vec2 = glm::vec2(glm::floor(vec2.x) + 25, glm::floor(vec2.y) + 25);
            std::tuple<int, int> t = ground_[int(vec2.x)][int(vec2.y)];
            if(std::get<1>(t) == 1 &&  std::get<0>(t) != this->id_)
            {
                //std::cout << int(vec2.x) << "\t"<< int(vec2.y) << "\t" << id_ << ":" << std::get<0>(t) << std::endl;
                return true;
            }
        }

        // step3: set this axis been occupied.
        for(glm::vec2 vec2 : points)
        {
            vec2 = glm::vec2(glm::floor(vec2.x) + 25, glm::floor(vec2.y) + 25);
            ground_[int(vec2.x)][int(vec2.y)] = std::make_tuple(this->id_, 1);
            std::cout << int(vec2.x) << "\t"<< int(vec2.y) << "\t" << id_ << ":" << std::endl;
        }
        return false;
    }

    void BuildModel()
    {
        glm::mat4 baseScale = glm::scale(glm::mat4(1.0), glm::vec3(base_scale, base_scale, base_scale));

        glm::mat4 torsoModel = glm::translate(glm::mat4(1.0), glm::vec3(base_x, base_y + 1.9*horse_dimension_.kTorsoHeight, base_z)) * RotateX(rotateX) * RotateY(rotateY) * RotateZ(rotateZ + theta[Torso]);
        //nodes[Torso] = Node(m, torso, NULL, &nodes[Neck]);
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f * horse_dimension_.kTorsoHeight, 0.0f));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kTorsoWidth, horse_dimension_.kTorsoHeight, horse_dimension_.kTorsoDepth));
        //glUniformMatrix4fv(glGetUniformLocation(shader_, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
        shader_.SetVector4f("shader_color", 0.0f,1.0f,0.7f,1.0f);
        torsoModel = baseScale * torsoModel;
        shader_.SetMatrix4("model", torsoModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 neckModel = glm::translate(glm::mat4(1.0), glm::vec3(-(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kNeckWidth / 2), horse_dimension_.kTorsoHeight, 0.0)) * RotateZ(theta[Neck]);
        //nodes[Neck] = Node(m, neck, &nodes[LeftUpperArm], &nodes[Head]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kNeckHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kNeckWidth, horse_dimension_.kNeckHeight, horse_dimension_.kNeckDepth));
        shader_.SetMatrix4("model", torsoModel * neckModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.8f,0.9f,0.75f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 headModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kNeckHeight, 0.0)) * RotateZ(theta[Head]);
        //nodes[Head] = Node(m, head, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kHeadHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kHeadWidth, horse_dimension_.kHeadHeight, horse_dimension_.kHeadDepth));
        shader_.SetMatrix4("model", torsoModel * neckModel * headModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.0f,0.6f,0.65f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 leftUpperArmModel = glm::translate(glm::mat4(1.0), glm::vec3(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperLegWidth / 2, 0.1*horse_dimension_.kUpperLegHeight, -horse_dimension_.kTorsoDepth/2 + horse_dimension_.kUpperLegWidth / 2)) * RotateZ(theta[LeftUpperArm]);
        //nodes[LeftUpperArm] = Node(m, left_upper_arm, &nodes[RightUpperArm], &nodes[LeftLowerArm]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperArmWidth, horse_dimension_.kUpperArmHeight, horse_dimension_.kUpperArmWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperArmModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.9f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 rightUpperArmModel = glm::translate(glm::mat4(1.0), glm::vec3(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperLegWidth / 2, 0.1*horse_dimension_.kUpperArmHeight, horse_dimension_.kTorsoDepth/2 - horse_dimension_.kUpperArmWidth / 2)) * RotateZ(theta[RightUpperArm]);
        //nodes[RightUpperArm] = Node(m, right_upper_arm, &nodes[LeftUpperLeg], &nodes[RightLowerArm]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperArmWidth, horse_dimension_.kUpperArmHeight, horse_dimension_.kUpperArmWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperArmModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.9f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 leftUpperLegModel = glm::translate(glm::mat4(1.0), glm::vec3(-(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperArmWidth / 2), 0.1*horse_dimension_.kUpperArmHeight, -horse_dimension_.kTorsoDepth/2 + horse_dimension_.kUpperArmWidth / 2)) * RotateZ(theta[LeftUpperLeg]);
        //nodes[LeftUpperLeg] = Node(m, left_upper_leg, &nodes[RightUpperLeg], &nodes[LeftLowerLeg]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperLegWidth, horse_dimension_.kUpperLegHeight, horse_dimension_.kUpperLegWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperLegModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.9f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 rightUpperLegModel = glm::translate(glm::mat4(1.0), glm::vec3(-(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperLegWidth / 2), 0.1*horse_dimension_.kUpperLegHeight, horse_dimension_.kTorsoDepth/2 - horse_dimension_.kUpperLegWidth / 2)) * RotateZ(theta[RightUpperLeg]);
        //nodes[RightUpperLeg] = Node(m, right_upper_leg, NULL, &nodes[RightLowerLeg]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperLegWidth, horse_dimension_.kUpperLegHeight, horse_dimension_.kUpperLegWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperLegModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.9f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glm::mat4 leftLowerArmModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperArmHeight, 0.0)) * RotateZ(theta[LeftLowerArm]);
        //nodes[LeftLowerArm] = Node(m, left_lower_arm, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerArmWidth, horse_dimension_.kLowerArmHeight, horse_dimension_.kLowerArmWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperArmModel * leftLowerArmModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.0f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 rightLowerArmModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperArmHeight, 0.0)) * RotateZ(theta[RightLowerArm]);
        //nodes[RightLowerArm] = Node(m, right_lower_arm, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerArmWidth, horse_dimension_.kLowerArmHeight, horse_dimension_.kLowerArmWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperArmModel * rightLowerArmModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.0f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 leftLowerLegModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperLegHeight, 0.0)) * RotateZ(theta[LeftLowerLeg]);
        //nodes[LeftLowerLeg] = Node(m, left_lower_leg, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerLegWidth, horse_dimension_.kLowerLegHeight, horse_dimension_.kLowerLegWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperLegModel* leftLowerLegModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.0f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 rightLowerLegModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperLegHeight, 0.0))* RotateZ(theta[RightLowerLeg]);
        //nodes[RightLowerLeg] = Node(m, right_lower_leg, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerLegWidth, horse_dimension_.kLowerLegHeight, horse_dimension_.kLowerLegWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperLegModel * rightLowerLegModel * translate * scale);
        shader_.SetVector4f("shader_color", 0.0f,0.9f,0.0f,1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    inline glm::mat4 RotateX(float f)
    {
        return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(1, 0, 0));
    }

    inline glm::mat4 RotateY(float f)
    {
        return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(0, 1, 0));
    }

    inline glm::mat4 RotateZ(float f)
    {
        return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(0, 0, 1));
    }

};
