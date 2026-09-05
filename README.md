# CProject (Unreal Portfolio)

Unreal Engine 4.26 기반 포트폴리오 프로젝트입니다.

## 요구 사항

- **Unreal Engine 4.26** (Epic Games Launcher로 설치)
- **Visual Studio 2019** ("게임 개발(C++)" 워크로드 포함)
- 마켓플레이스 플러그인 (엔진에 설치 필요, 프로젝트에는 포함되어 있지 않음)
  - [ElectronicNodes](com.epicgames.launcher://ue/marketplace/content/5cb2a394d0c04e73891762be4cbd7216)
  - [FootIK](com.epicgames.launcher://ue/marketplace/product/30658ca1ebb647d29973849d70efabe7)

## 재설치 방법

1. 저장소 클론
   ```
   git clone https://github.com/kjejhk37/unreal_cpp_4_26_portfolio.git
   ```
2. Epic Games Launcher에서 위 마켓플레이스 플러그인 2개를 라이브러리에 추가/설치 (엔진 버전 4.26용)
3. `CProject.uproject` 파일 우클릭 → **Generate Visual Studio project files**
   - `.sln` 파일과 `Intermediate/`, `Binaries/` 등은 git에서 제외되어 있어 이 과정에서 새로 생성됩니다.
4. `CProject.sln` 열어서 Development Editor 구성으로 빌드 (또는 `.uproject` 더블클릭 시 자동 빌드 프롬프트)
5. 빌드 완료 후 `.uproject` 더블클릭으로 에디터 실행

## 알아둘 점

- **`Content/DepthsBelow/Maps/Map_Main_BuiltData.uasset` 제외됨** — 라이팅 빌드 캐시 파일로 458MB라 GitHub 파일 크기 제한(100MB)을 초과해서 커밋하지 않았습니다. `Map_Main` 맵을 열면 "라이팅을 다시 빌드해야 합니다" 경고가 뜨는 게 정상이며, 에디터 메뉴 **Build → Build Lighting Only**(또는 Build All Levels)로 재생성하면 됩니다.
- `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, `.vs/` 폴더는 전부 빌드/캐시 산출물이라 `.gitignore`로 제외했습니다. 위 3번 단계에서 프로젝트 파일을 재생성하고 빌드하면 자동으로 다시 만들어집니다.
