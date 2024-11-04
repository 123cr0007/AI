#include "Bone.h"


// 1�ځ[��IK
void OneBoneIK(VECTOR targetPos, VECTOR& bonePos, VECTOR& boneDir) {

    // �@IK�̖ڕW�ʒu�����[�J���ɕϊ�
    VECTOR localTargetPos = VSub(targetPos, bonePos);
    // ���K�����ĕ����x�N�g���ɂ���
    VECTOR localTargetDir = VNorm(localTargetPos);

    // sq = squared�̗��ŁA2���\��
    float sqX = localTargetPos.x * localTargetPos.x;
    float sqY = localTargetPos.y * localTargetPos.y;
    float sqZ = localTargetPos.z * localTargetPos.z;

    // �O�����̒藝�Ńx�N�g���̒��������߂�
    float length = sqrt(sqX + sqY + sqZ);


    // �A���[�J�����W����O�p���p����sin��z, cos��z, sin��y, cos��y���v�Z
    // 2.1 ���[�p���v�Z����
    // DxLib��Y-up�Ȃ̂�sin��y, cos��y���v�Z����(Z-up����sin��z, cos��z�ɂȂ�)
    float cosTY = localTargetPos.x / sqrt(sqX + sqZ);
    float sinTY = localTargetPos.z / sqrt(sqX + sqZ);

    // 2.2 �s�b�`�p���v�Z����
    // sin��x, cos��x���v�Z����
    float cosTZ = sqrt(sqX + sqZ) / length;
    float sinTZ = localTargetPos.y / length;


    // �B�{�[���̌��������߂�
    // 3.1 ���[���̉�]�s������
    // �O���[�o����Y���i������j
    VECTOR yawAxis = VGet(0.0f, 1.0f, 0.0f);
    if (localTargetDir.x == 0.0f && localTargetDir.z == 0.0f) {
        yawAxis = VGet(1.0f, 0.0f, 0.0f); // ����P�[�X: �ڕW��Y���ɉ����Ă���ꍇ�AX������]���ɂ���
    }
    MATRIX rotationYaw = MGetRotAxis(yawAxis, atan2(sinTY, cosTY));

    // 3.2 �s�b�`���̉�]�s������
    // �O���[�o����X���i�E�����j
    VECTOR pitchAxis = VGet(1.0f, 0.0f, 0.0f);
    MATRIX rotationPitch = MGetRotAxis(pitchAxis, atan2(sinTZ, cosTZ));

    // �{�[���̕������X�V
    // �����K�����[���s�b�`�̏��ԂŊ|����
    boneDir = VTransform(boneDir, rotationYaw);
    boneDir = VTransform(boneDir, rotationPitch);
}


void TwoBoneIK(VECTOR targetPos, VECTOR& joint1Pos, VECTOR& joint1Dir,
    VECTOR& joint2Pos, VECTOR& joint2Dir, float bone1Length, float bone2Length) {

    VECTOR Line = VSub(targetPos, joint1Pos);
    float LineLength = VSize(Line);

    // �@1�{�[��IK���g���đ��֐߂�ڕW�ʒu�Ɍ�����
    OneBoneIK(targetPos, joint1Pos, joint1Dir);

    // �A���֐߂̐i�s��������Ƃ��đ��֐߂̉�]����@���Ƃ��镽�ʂ����
    VECTOR planeNormal = VCross(joint1Dir, VSub(targetPos, joint1Pos));
    planeNormal = VNorm(planeNormal); // �@���̐��K��

    // ��������͑��֐߂����֐߂���̖@�������Ƃ����P����]�����邽�߁A�Q�����̖��Ƃ��Ĉ���
    // �B���֐߂̐�[���ڕW�ʒu�Ɍ����悤�ɓ�{�̊֐߂���]�����āA�O�p�`�����  
    // 3.1�O�p�`�̊e�ӂ́A���ꂼ��bone1Length, bone2Length, Line�̒��������̂�
    // ��a��bone1Length�A��b��bone2Length�A��c��Line�Ƃ��ė]���藝���g����cosB,C�����߂�
    float sqA = bone1Length * bone1Length;
    float sqB = bone2Length * bone2Length;
    float sqC = LineLength * LineLength;

    float cosB = (sqA + sqC - sqB) / (2 * bone1Length * LineLength);
    clanp1m1(cosB); // -1�`1�͈̔͂ɃN�����v
    float sinB = sqrt(1 - cosB * cosB);

    float cosC = (sqA + sqB - sqC) / (2 * bone1Length * bone2Length);
    clanp1m1(cosC); // -1�`1�͈̔͂ɃN�����v
    float sinC = sqrt(1 - cosC * cosC);

    // 3.3��]�����ɂ��čl����O�ɁA��2�֐߂̉�]�p���]���藝�ŋ��߂��O�p�`abc�̓��pC�ł͂Ȃ��A
    // ���ۂɂ͊O�p�̃�-C�ƂȂ��Ă���_�ɂ��čl�����Ȃ���΂Ȃ�܂���B
    // �Ƃ����Ă��A�����͈ȉ��̌����ɂ���������cosC�̕����𔽓]���邾���ō\���܂���BsinC�̒l�͂��̂܂܂ł��B
    cosC = -cosC; // �O�p�␳

    // �C��]��������sin�ɂ����������߂�
    // ��]�����������v���̏ꍇ�͐������̉�]�ŁA���v���̏ꍇ�͕������̉�]�ƂȂ�B
    // ��]�����̐�����sin�Ƃ̐��������ŕ\���ł���̂ŁAcos�̕����͕ω����Ȃ��B
    // �����ŁAsin�Ƃ̐����͊O�ς��g���ċ��߂邱�Ƃ��ł���B
    // �����ŁA�O�ς̌��ʂ����̏ꍇ��sin�Ƃ����A���̏ꍇ��sin�Ƃ����ƂȂ�B
    if (VSize(VCross(joint1Dir, VSub(targetPos, joint1Pos))) < 0) {
        sinB = -sinB;
    }

    // �D����ꂽcos, sin�̑g�ݍ��킹�ŁA�e�֐߂���]������
    // joint1�̐V���������x�N�g�����v�Z
    MATRIX rotationB = MGetRotAxis(planeNormal, atan2(sinB, cosB));
    joint1Dir = VTransform(joint1Dir, rotationB);
    joint1Dir = VNorm(joint1Dir); // ���K��

    // joint2�̈ʒu���v�Z
    joint2Pos = VAdd(joint1Pos, VScale(joint1Dir, bone1Length));
    // joint2�̐V���������x�N�g�����v�Z
    MATRIX rotationC = MGetRotAxis(planeNormal, atan2(sinC, cosC));
    joint2Dir = VTransform(joint1Dir, rotationC);
    joint2Dir = VNorm(joint2Dir); // ���K��
}