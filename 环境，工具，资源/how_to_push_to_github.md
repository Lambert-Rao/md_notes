### 关于如何把git记录提交到GitHub

因为GitHub关闭了使用密码验证git的功能，所以我们需要在GitHub上获取令牌。

1. 首先，你需要登录你的GitHub帐户。
2. 点击右上角的头像，然后选择“设置”（Settings）。
3. 在左侧的侧边栏中，点击“开发者设置”（Developer settings）。
4. 然后选择“个人访问令牌”（Personal access tokens）。
5. 点击右上角的“生成新令牌”（Generate new token）按钮。
6. 然后你需要在“注释”（Note）中输入一个描述这个令牌如何使用的简短说明（用来git）。
7. 在下面的“选择范围”（Select scopes）部分，你可以选择你希望这个令牌具备哪些权限。如果要克隆，只需要给予 `read:packages` 和 `repo` 这两个权限。如果你需要推送代码，那么你还需要 `write:packages` 和 `delete:packages`权限。
8. 在设置完所有选项之后，点击页面底部的“生成令牌”（Generate token）按钮。

接下来你在使用`git push`的时候，就会自动询问你用户名和密码，只要在密码这里填入刚才拿到的`token`就行了。而如果你不想每次都输入`token`（似乎你也记不住），那么你需要使用这条命令：

```bash
git config --global credential.helper store
```

这将创建一个未加密的文件（默认在 `~/.git-credentials`），在此文件中存储你的凭证。然后，当你第一次需要输入令牌时，Git 会记住它，并在之后需要使用时自动填写。***但是要注意，这个文件是未加密的，所以你应当确保它的安全。***

然后万事大吉。

另外推荐一下lazygit.
